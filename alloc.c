// File:	my_pthread_t.h
// Author:	Bruno J. Lucarelli
// Date:	02-22-17
// username of iLab: bjl145
// iLab Server: man.cs.rutgers.edu

#include "alloc.h"

/* General support functions defined here. */

intNode createIntNode(int value) {
	intNode newNode = (intNode) malloc(sizeof(struct integerNode));
	newNode->val = value;
	newNode->next = NULL;
	return newNode;
}

regNode createRegNode(uint id) {
	regNode newNode = (regNode) malloc(sizeof(struct registerNode)); 
	newNode->id = id;
	// SPECIAL CASE: r0 is always in a physical register of ID 0.
	if(id == 0) {
		newNode->status = PHYS;
		newNode->physId = 0;
	}
	// otherwise, give default values.
	else {
		newNode->status = NONE;
		newNode->physId = 999;
	}
	newNode->firstOcc = NULL;
	newNode->offset = 9001;
	newNode->next = NULL;
	newNode->firstInstr = -1;
	newNode->lastInstr = -1;
	newNode->nextUse = -1;
	return newNode;
}

void freeRegNode(regNode input) {
	// first, free the list of occurrences.
	freeIntNode(input->firstOcc);
	// then free the current regNode.
	free(input);
	return;
}

int nextNum(char *line, int *currIndexPtr) {
	// index value passed in from the pointer.
	int currIndex = *currIndexPtr;
	// value we'll use to store the return value.
	int ret = -1;
	// set currIndex to the first numeric value.
	while(line[currIndex] < '0' || line[currIndex] > '9') {
		currIndex += 1;
	}
	// set lastIndex to currIndex, and then move it to the first non-numeric value.
	int lastIndex = currIndex;
	while(line[lastIndex] >= '0' && line[lastIndex] <= '9') {
		lastIndex += 1;	
	}
	// obtain the length of the constant.
	int length = lastIndex - currIndex;
	// copy the constant to a null-terminated string.
	char constStr[length + 1];
	constStr[length] = '\0';
	strncpy(constStr, &(line[currIndex]), length);
	// obtain the value of the constant.
	ret = strtol(constStr, NULL, 10);
	// update the index stored at the pointer, and return.
	*currIndexPtr = lastIndex;
	return ret;
}
	

void addOccToReg(int val, uint targetReg, regNode head) {
	// First, obtain the regNode corresponding to parameter id, if any.
	regNode currReg = head;
	while(currReg != NULL) {
		if(currReg->id == targetReg) {
			break;
		}
		currReg = currReg->next;
	}
	// If target register not present, return.
	if(currReg == NULL) {
		printf("Error in addOccToReg()! Register r%d not present, but attempting to add occurrence at line %d\n",
			targetReg, val);
		exit(EXIT_FAILURE);
	}
	// Otherwise, continue on and attempt to add the occurrence.
	addIntNode(val, &(currReg->firstOcc));
	return;
}

void addReg(uint id, regNode head) {
	// First: determine if the register already exists. Return if it does.
	regNode curr = head;
	// Just a search of the linked list.
	while(curr != NULL) {
		if(curr->id == id) {
			return;
		}
		curr = curr->next;
	}
	
	// If the register doesn't already exist, create it and insert it at the
	// very end of the list.
	curr = head;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	regNode newNode = createRegNode(id);
	curr->next = newNode;
	return;
}

regNode genRegList(FILE *file) {
	// Getting started: let's go through the file and print every line that isn't
	// a blank space, or that isn't a comment. Go until EOF.
	ssize_t read = 0;
	ssize_t len = 0;
	char *currLine = NULL;
	// These variables store, respectively, the first regNode in the list, and
	// the current/last regNode currently in the list.
	regNode firstNode = NULL;
	regNode currNode = NULL;
	// This variable acts as a counter of the current instruction. Comments and blank lines
	// are NOT included in the instruction count.
	uint currInstr = 0;
	// Let's go to each non-blank line and obtain the type of the operation, plus
	// the (up to three) registers involved. Registers will be obtained in order
	// of appearance, and a register can appear more than once in an operation;
	while(read = getline(&currLine, &len, file) != -1) {
		// Ignore a blank line or a comment.
		if(strlen(currLine) != 1 && currLine[0] != '/') {
			// First, find the index of the initial non-blank character.
			uint currIndex = 0;
			uint firstIndex = 0;
			char currChar = currLine[currIndex];
			while(isblank(currChar)) {
				currIndex += 1;
				currChar = currLine[currIndex];
			}
			firstIndex = currIndex;
			// Now find the index of the first blank character following it.
			uint lastIndex = currIndex;
			while(!isblank(currChar)) {
				currIndex += 1;
				currChar = currLine[currIndex];
			}
			lastIndex = currIndex;
			// The length of the actual operation string will be 1 more than the
			// difference between the two indexes. Copy the operation string
			// over to a null-terminated stack buffer, to prepare for comparison.
			uint opLength = lastIndex - firstIndex;
			char opString[opLength + 1];
			opString[opLength] = '\0';
			strncpy(opString, &(currLine[firstIndex]), opLength);
			// Any operation may have up to 3 registers involved (duplicates allowed),
			// and one constant value. 
			int opReg1 = -1;
			int opReg2 = -1;
			int opReg3 = -1;
			int opConst = -1;
			if(strcmp(opString, "loadI") == 0) {
				// next value would be a constant.
				opConst = nextNum(currLine, &currIndex);
				// following that, a register.
				opReg1 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "load") == 0 || strcmp(opString, "store") == 0) {
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "add") == 0 || strcmp(opString, "sub") == 0 ||
					strcmp(opString, "mult") == 0 || strcmp(opString, "lshift") == 0 ||
					strcmp(opString, "rshift") == 0) {
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "output") == 0) {
				// value would be a constant.
				opConst = nextNum(currLine, &currIndex);
			}
			else{
				printf("ERROR! No valid operation provided.\n");
				exit(EXIT_FAILURE);
			}
			// FIRST CASE: if firstNode is NULL, set it to the first of the registers
			// that appears.
			if(firstNode == NULL) {
				if(opReg1 != -1) {
					firstNode = createRegNode(opReg1);
				}
				else if(opReg2 != -1) {
					firstNode = createRegNode(opReg2);
				}
				else if(opReg3 != -1) {
					firstNode = createRegNode(opReg3);
				}
				else {
					printf("ERROR! opReg all -1, but just finished parsing line in genRegList()\n.");
					exit(EXIT_FAILURE);
				}
			}
			// NORMAL CASE: firstNode is not NULL. Attempt to add each register and the
			// occurrence number for each register. Note that if the register and/or
			// occurrence already exists, each respective operation is ignored by the function.
			if(opReg1 != -1) {
				addReg(opReg1, firstNode);
				addOccToReg(currInstr, opReg1, firstNode);
			}
			if(opReg2 != -1) {
				addReg(opReg2, firstNode);
				addOccToReg(currInstr, opReg2, firstNode);
			}
			if(opReg3 != -1) {
				addReg(opReg3, firstNode);
				addOccToReg(currInstr, opReg3, firstNode);
			}
			// increment the instruction number, since we've successfully finished a valid instruction.
			currInstr += 1;
		}
		// free the current line's memory, and set the pointer to null
		free(currLine);
		currLine = NULL;
	}
	// For each regNode, update its liveStart and liveEnd members.
	currNode = firstNode;
	// Go through each regNode.
	while(currNode != NULL) {
		// For each regNode, record the first and last occurrence.
		int currFirstOcc = 9001;
		int currLastOcc = 9001;
		intNode currOcc = currNode->firstOcc;
		currFirstOcc = currOcc->val;
		while(currOcc->next != NULL) {
			currOcc = currOcc->next;
		}
		currLastOcc = currOcc->val;
		// set beginning of live range to first occurrence
		currNode->firstInstr = currFirstOcc;
		// note: live range ends 1 instruction before last occurrence, 
		currNode->lastInstr = currLastOcc;
		currNode = currNode->next;
	}
	// Be kind: Rewind (the file pointer)!
	rewind(file);
	return firstNode;
}

void printRegNode(regNode node) {
	printf("contents of r%d:\n", node->id);
	printf("status: %d\n", node->status);
	printf("occs: ");
	intNode currOcc = node->firstOcc;
	while(currOcc != NULL) {
		printf("%d, ", currOcc->val);
		currOcc = currOcc->next;
	}
	printf("\n");
	printf("physical ID (if applicable): %d\n", node->physId);
	printf("offset in memory (if applicable): %d\n", node->offset);
	printf("first instruction: %d\n", node->firstInstr);
	printf("last instruction: %d\n", node->lastInstr);
	return;
}

void printRegList(regNode head) {
	regNode currReg = head;
	// iterate through each register node and print all of the contents.
	while(currReg != NULL) {
		printRegNode(currReg);
		currReg = currReg->next;
	}
	return;
}

int intNodeExists(int target, intNode head) {
	intNode currNode = head;
	while(currNode != NULL) {
		if(currNode->val == target) {
			return 1;
		}
		currNode = currNode->next;
	}
	return -1;
}

void freeIntNode(intNode head) {
	if(head == NULL) {
		return;
	}
	intNode currNode = head;
	while(currNode != NULL) {
		intNode nextNode = currNode->next;
		free(currNode);
		currNode = nextNode;
	}
	return;
}

regNode getRegNode(uint id, regNode head) {
	regNode currNode = head;
	while(currNode != NULL) {
		if(currNode->id == id) {
			return currNode;
		}
		currNode = currNode->next;
	}
	return NULL;
}

void spillReg(uint targetId, uint physId, regNode head) {
	// obtain the regNode instance we want to spill/modify
	regNode targetNode = getRegNode(targetId, head);
	if(targetNode == NULL) {
		printf("Error in spillReg! Target %d doesn't exist!\n", targetId);
		exit(EXIT_FAILURE);
	}
	// obtain its offset
	int offset = targetNode->offset;
	// print the spill operation to standard output
	fprintf(stdout, "storeAI r%d => r0, %d\n", physId, offset);
	// modify the target node's physId to 999 (default)
	targetNode->physId = 999;
	return;
}

void fetchReg(uint targetId, uint physId, regNode head) {
	// obtain the regNode instance we want to fetch/modify
	regNode targetNode = getRegNode(targetId, head);
	if(targetNode == NULL) {
		printf("Error in fetchReg! Target %d doesn't exist!\n", targetId);
		exit(EXIT_FAILURE);
	}
	// obtain its offset
	int offset = targetNode->offset;
	// print the loadAI operation to standard output
	fprintf(stdout, "loadAI r0, %d => r%d\n", offset, physId);
	// modify the target node's physId to that of the physical register
	targetNode->physId = physId;
	return;
}

regNode *sortedRegArr(regNode head, TD_TYPE type) {
	// First, get the length of the linked list.
	int listLength = 0;
	regNode currNode = head;
	while(currNode != NULL) {
		listLength += 1;
		currNode = currNode->next;
	}
	currNode = head;
	// Next, add each regNode (pointer) to a regNode array. This is the mid-point
	// array which we'll sort using qsort(). Not to be confused with the return array.
	regNode midArr[listLength - 1];
	int index = 0;
	while(currNode != NULL) {
		// Don't add r0 to the array, as it doesn't get an allocatable register.
		if(currNode->id != 0) {
			// Add the register to the array.
			midArr[index] = currNode;
			index += 1;
		}
		currNode = currNode->next;
	}
	if(type == SIMPLE) {
		// Sort midArr using qsort() and descComp.
		qsort((void *) midArr, listLength - 1, sizeof(regNode), descComp);
	}
	else if(type == LIVE) {
		// Sort midArr using qsort() and descCompLive.
		qsort((void *) midArr, listLength - 1, sizeof(regNode), ascCompLive);
	}
	else{
		printf("ERROR in sortedRegArr! Invalid flag: %d\n", type);
		exit(EXIT_FAILURE);
	}
	// Transfer midArr to a dynamically-allocated return array.
	regNode *retArr = (regNode *) malloc(listLength * sizeof(regNode));
	retArr[listLength-1] = NULL;
	int i;
	for(i = 0; i < listLength-1; i++) {
		retArr[i] = midArr[i];
	}	
	return retArr;
}

int intNodeListLength(intNode head) {
	intNode curr = head;
	int length = 0;
	while(curr != NULL) {
		length += 1;
		curr = curr->next;
	}
	return length;
}

int regNodeListLength(regNode head) {
	regNode curr = head;
	int length = 0;
	while(curr != NULL) {
		if(curr->id != 0) {
			length += 1;
		}
		curr = curr->next;
	}
	return length;
}

void deleteIntNode(int target, intNode *headPtr) {
	intNode currNode = *headPtr;
	intNode prevNode = NULL;
	// iterate through each node
	while(currNode != NULL) {
		// first case: currNode is target, and prevNode is NULL, meaning that current node is head.
		if(currNode->val == target && prevNode == NULL) {
			// delink the head from the list, free it, and change the head reference
			prevNode = currNode->next;
			free(currNode);
			currNode = prevNode;
			// note that we change the value referenced by headPtr to be the next node in the sequence.
			*headPtr = currNode;
			break;
		}
		// normal case: currNode is target and prevNode is not NULL, meaning that current node can be
		// delinked in middle.
		else if(currNode->val == target && prevNode != NULL) {
			prevNode->next = currNode->next;
			free(currNode);
			break;
		}
		// otherwise, iterate as normal
		else{
			prevNode = currNode;
			currNode = currNode->next;
		}
	}
	return;
}

void addIntNode(int val, intNode *intHeadPtr) {
	intNode newNode = createIntNode(val);
	// First case: if the regNode has no occurrences, change the pointer to reference a new head.
	intNode currNode = *intHeadPtr;
	if(currNode == NULL) {
		*intHeadPtr = newNode;
		return;
	}
	// Normal case: first node is occupied and not the same as the input. Iterate through the list. 
	// If the occurrence isn't present, add it to the very end.
	while(currNode != NULL) {
		// Return if we've found the occurrence already present.
		if(currNode->val == val) {
			free(newNode);
			return;
		}
		if(currNode->next == NULL) {
			break;
		}
		currNode = currNode->next;
	}
	// If we've reached the end without a match, add newNode to the end, then return.
	currNode->next = newNode;
	return;
}

/* Top-down allocation (simple) support functions defined here. */

int descComp(const void *in1, const void *in2) {
	// cast the inputs to regNodes
	regNode n1 = *((regNode *) in1);
	regNode n2 = *((regNode *) in2);
	// obtain number of occurrences of each register
	intNode currNode = n1->firstOcc;
	currNode = n2->firstOcc;
	int n1Count = intNodeListLength(n1->firstOcc);
	int n2Count = intNodeListLength(n2->firstOcc);
	// return -1 if first register has more occs than second
	if(n1Count > n2Count) {
		return -1;
	}
	// return 0 if they have same number of occs
	else if(n1Count == n2Count) {
		return 0;
	}
	// return 1 if first register has fewer occs than second
	else {
		return 1;
	}
}

void topDownSimple(int numRegisters, FILE *file) {
	// First, obtain the linked list of regNodes from the file.
	regNode head = genRegList(file);
	// Next, obtain a dynamically-allocated array of regNodes that's sorted by
	// descending order of occurrences.
	regNode *sortedRegs = sortedRegArr(head, SIMPLE);
	// Start allocating physical registers at either r1 (number of physical registers >=
	// number of virtual registers, or r3 (2 feasible registers).
	uint currId;
	int availableRegs = 0;
	// determine how many virtual registers there are. ignore r0!
	int length = regNodeListLength(head);
	// if there are enough registers to ignore feasible register requirements, make all
	// of the registers available.
	if(numRegisters >= length) {
		currId = 1;
		availableRegs = numRegisters;
	}
	// otherwise, start allocating at 3, and let k - F registers be available.
	else{
		currId = 3;
		availableRegs = numRegisters - 2;
	}
	int index = 0;
	regNode currReg = sortedRegs[index];
	// Allocate as many physical registers as we have available for such, until we
	// either run out of physical registers or virtual registers (in sortedRegs).
	while(availableRegs > 0 && sortedRegs[index] != NULL) {
		// Give the currId as a physically-allocated space to the next virtual register
		// in line, and change its status, unless it's r0. Otherwise we just continue
		// as usual.
		if(currReg->id != 0) {
			currReg = sortedRegs[index];
			currReg->status = PHYS;
			currReg->physId = currId;
			availableRegs -= 1;
			currId += 1;
		}
		index += 1;
	}
	// Start allocating offsets at -4 (as in r0, -4).
	int currOffset = -4;
	index = 0;
	currReg = sortedRegs[0];
	// Allocate offsets and set statuses for regNodes who didn't get a physically-allocated
	// register before.
	while(currReg != NULL) {
		if(currReg->status != PHYS) {
			currReg->status = MEM;
			currReg->offset = currOffset;
			currOffset -= 4;
		}
		index += 1;
		currReg = sortedRegs[index];
	}
	// Now that the physical registers have been allocated (if any), we provide output
	// contingent with what we find line-by-line.
	// Getting started: let's go through the file and perform top-down operations on
	// every non-blank line.
	ssize_t read = 0;
	ssize_t len = 0;
	char *currLine = NULL;
	// Let's go to each non-blank line and fetch it. Then use opTD() to process
	// the line and provide the according output.
	while(read = getline(&currLine, &len, file) != -1) {
		// Ignore a blank line or a comment.
		if(strlen(currLine) != 1 && currLine[0] != '/') {
			// perform the operation(s) for this line
			opTD(currLine, head);
		}
		// free the current line's memory, and set the pointer to null
		free(currLine);
		currLine = NULL;
	}
	// Be kind: Rewind (the file pointer)!
	rewind(file);


	// free the structs of the regNode list
	freeRegNode(head);
	// free the sorted register array (only an array of pointers, not structs):
	free(sortedRegs);
	return;
}

void opTD(char *currLine, regNode head) {
	// First, find the index of the initial non-blank character.
	uint currIndex = 0;
	uint firstIndex = 0;
	char currChar = currLine[currIndex];
	while(isblank(currChar)) {
		currIndex += 1;
		currChar = currLine[currIndex];
	}
	firstIndex = currIndex;
	// Now find the index of the first blank character following it.
	uint lastIndex = currIndex;
	while(!isblank(currChar)) {
		currIndex += 1;
		currChar = currLine[currIndex];
	}
	lastIndex = currIndex;
	// The length of the actual operation string will be 1 more than the
	// difference between the two indexes. Copy the operation string
	// over to a null-terminated stack buffer, to prepare for comparison.
	uint opLength = lastIndex - firstIndex;
	char opString[opLength + 1];
	opString[opLength] = '\0';
	strncpy(opString, &(currLine[firstIndex]), opLength);
	// Any operation may have up to 3 registers involved (duplicates allowed),
	// and one constant value. 
	if(strcmp(opString, "loadI") == 0) {
		// loadI 5 => r6
		// next value would be a constant.
		int constant = nextNum(currLine, &currIndex);
		// following that, a register.
		uint outReg = nextNum(currLine, &currIndex);
		regNode outRegNode = getRegNode(outReg, head);
		uint physReg;
		// if the output register is allocated, use its allocated physical register.
		if(outRegNode->status == PHYS) {
			physReg = outRegNode->physId;
		}
		// if the output register isn't allocated, use the first available feasible
		// register and then spill it to the virtual register's offset.
		else{
			physReg = 1;
		}
		fprintf(stdout, "loadI %d => r%d\n", constant, physReg);
		if(outRegNode->status == MEM) {
			spillReg(outReg, physReg, head);
		}
	}
	else if(strcmp(opString, "load") == 0) {
		// load r1 => r2 means: load MEM[r1] into r2
		// next value would be a register.
		uint inReg = nextNum(currLine, &currIndex);
		// following that, another register.
		uint outReg = nextNum(currLine, &currIndex);
		uint inPhysReg;
		uint outPhysReg;
		regNode inRegNode = getRegNode(inReg, head);
		regNode outRegNode = getRegNode(outReg,head);
		// if the input register is allocated, use that physical register.
		if(inRegNode->status == PHYS) {
			inPhysReg = inRegNode->physId;
		}
		// otherwise, use the first feasible register and fetch the value into that.
		else{
			inPhysReg = 1;
			fetchReg(inReg, inPhysReg, head);
		}
		// if the output register is allocated, use that.
		if(outRegNode->status == PHYS) {
			outPhysReg = outRegNode->physId;
		}
		// otherwise, use the second feasible register and spill the value after
		// the operation.
		else{
			outPhysReg = 2;
		}
		fprintf(stdout, "load r%d => r%d\n", inPhysReg, outPhysReg);
		if(outRegNode->status == MEM) {
			spillReg(outReg, outPhysReg, head);
		}

	}
	else if(strcmp(opString, "store") == 0) {
		// store r1 => r2 means: store r1 into MEM[r2]
		// next value would be a register.
		uint inReg = nextNum(currLine, &currIndex);
		// following that, another register.
		uint outReg = nextNum(currLine, &currIndex);
		uint inPhysReg;
		uint outPhysReg;
		regNode inRegNode = getRegNode(inReg, head);
		regNode outRegNode = getRegNode(outReg,head);
		// if the input register is allocated, use that physical register.
		if(inRegNode->status == PHYS) {
			inPhysReg = inRegNode->physId;
		}
		// otherwise, use the first feasible register and fetch the value into that.
		else{
			inPhysReg = 1;
			fetchReg(inReg, inPhysReg, head);
		}
		// treat the output register the same way, since it's being read from rather than
		// written to (its memory is what's touched). it thus uses the second feasible
		// register (in case r1 is taken) if needed.
		if(outRegNode->status == PHYS) {
			outPhysReg = outRegNode->physId;
		}
		else{
			outPhysReg = 2;
			fetchReg(outReg, outPhysReg, head);
		}
		fprintf(stdout, "store r%d => r%d\n", inPhysReg, outPhysReg);
	}
	// can i lump in add, sub, mult, lshift, and rshift into one contingent branch?
	// they function identically, syntactically speaking. 
	else if(strcmp(opString, "add") == 0 || strcmp(opString, "sub") == 0 || strcmp(opString, "mult") == 0
		 || strcmp(opString, "lshift") == 0 || strcmp(opString, "rshift") == 0) {
		// add r2, r3 => r4; add r2, r2 => r3; add r2, r2 => r2; so on.
		// sub r2, r3 => r4; sub r2, r2 => r3; sub r2, r2 => r2; so on.
		// same syntax for mult, lshift, and rshift.
		uint inReg1 = nextNum(currLine, &currIndex);
		uint inReg2 = nextNum(currLine, &currIndex);
		uint outReg = nextNum(currLine, &currIndex);
		uint inPhysReg1;
		uint inPhysReg2;
		uint outPhysReg;
		int f1Used = 0;
		regNode inRegNode1 = getRegNode(inReg1, head);
		regNode inRegNode2 = getRegNode(inReg2, head);
		regNode outRegNode = getRegNode(outReg, head);
		// if the first input is already allocated, use that.
		if(inRegNode1->status == PHYS) {
			inPhysReg1 = inRegNode1->physId;
		}
		// otherwise, use the first feasible register and fetch the value into that.
		else{
			inPhysReg1 = 1;
			fetchReg(inReg1, inPhysReg1, head);
			f1Used = 1;
		}
		// if the second input equals the first input, use inPhysReg1 for inPhysReg2.
		if(inReg2 == inReg1){
			inPhysReg2 = inPhysReg1;
		}
		// otherwise, same drill as before.
		else {
			// use the second input's physical register as applicable
			if(inRegNode2->status == PHYS) {
				inPhysReg2 = inRegNode2->physId;
			}
			// otherwise, fetch it into one of the feasible registers
			else{
				// If first feasible register isn't used, use that.
				if(f1Used != 1) {
					inPhysReg2 = 1;
				}
				// Otherwise, use second feasible register.
				else{
					inPhysReg2 = 2;
				}
				fetchReg(inReg2, inPhysReg2, head);
			}
		}
		// output register: if it has a physical register, use that.
		if(outRegNode->status == PHYS) {
			outPhysReg = outRegNode->physId;
		}
		// otherwise, use the first feasible register for output.
		else {
			outPhysReg = 1;
		}
		// print out the message given that we know the registers now.
		fprintf(stdout, "%s r%d, r%d => r%d\n", opString, inPhysReg1, inPhysReg2, outPhysReg);
		// if the output is in memory, spill the output register to there.
		if(outRegNode->status == MEM) {
			spillReg(outReg, outPhysReg, head);
		}

	}
	else if(strcmp(opString, "output") == 0) {
		// output 1028
		// value would be a constant.
		int constant = nextNum(currLine, &currIndex);
		// pretty straightforward. just print the message right here.
		fprintf(stdout, "output %d\n", constant);
	}
	else{
		printf("ERROR! No valid operation provided.\n");
		exit(EXIT_FAILURE);
	}
}


/* Top-down allocation (lecture, or LIVE version) support functions defined here. */

void chooseAndSpill(int instr, int allocatableRegs, PHYS_STATUS *physStatuses, int *currOffset, regNode head, intNode *liveListPtr) {
	// add any node to liveList which became live at this instruction, AND which isn't already spilled,
	// AND which isn't r0
	intNode liveList = *liveListPtr;
	regNode currReg = head;
	while(currReg != NULL) {
		if(currReg->status != MEM && currReg->id != 0 && currReg->firstInstr == instr) {
			addIntNode(currReg->id, &liveList);
		}
		currReg = currReg->next;
	}
	// if the number of live registers at the moment is greater than the number of allocatable registers,
	// we need to spill some.
	int numLive = intNodeListLength(liveList);
	if(numLive > allocatableRegs) {
		// number of registers that must be spilled
		int numToSpill = numLive - allocatableRegs;
		// array of registers sorted in ascending order of occurrences, tie-breaker live range
		regNode *sortedArr = sortedRegArr(head, LIVE);
		// iterate through sortedArr numToSpill times.
		int nextOffset = *currOffset;
		int index = 0;
		int lengthArr = regNodeListLength(head);
		while(index < lengthArr) {
			// if the register in question matches one in liveList, change its properties to indicate
			// that it's spilled.
			if(intNodeExists(sortedArr[index]->id, liveList) == 1) {
				sortedArr[index]->status = MEM;
				sortedArr[index]->offset = nextOffset;
				// make the physical register free if applicable ("you no longer get a physical register")
				int physId = sortedArr[index]->physId;
				physStatuses[physId - 3] = FREE;
				// decrement to the next available offset
				nextOffset -= 4;
				// one less register to spill
				numToSpill -= 1;
			}
			// if we've spilled as many registers as needed, break the loop
			if(numToSpill == 0) {
				break;
			}
			index += 1;
		}
		// modify currOffset to reflect the next available offset.
		*currOffset = nextOffset;
		// free sortedArr
		free(sortedArr);
	}
	// go through liveList and delink any registers with a status of MEM
	intNode currInt = liveList;
	while(currInt != NULL) {
		// if the status is MEM:
		regNode currReg = getRegNode(currInt->val, head);
		if(currReg->status == MEM) {
			// capture this intNode's value
			int id = currInt->val;
			// iterate currInt to the next available node (could end up freeing currInt,
			// need to iterate here first)
			currInt = currInt->next;
			// delink the current node from liveList
			deleteIntNode(id, &liveList);
		}
		// otherwise, keep iterating through
		else{
			currInt = currInt->next;
		}
	}
	*liveListPtr = liveList;
	return;
}

void chooseAndAllocate(int instr, int allocatableRegs, PHYS_STATUS *physStatuses, regNode head, intNode *liveListPtr) {
	intNode liveList = *liveListPtr;
	intNode currInt = liveList;
	// first pass: delink and release physical registers for any virtual registers no longer live
	while(currInt != NULL) {
		// obtain the register corresponding to this intNode
		regNode currReg = getRegNode(currInt->val, head);
		// if its last instruction equals this instruction (live on exit)
		if(currReg->lastInstr == instr) {
			// obtain the physical register ID of the regNode
			uint physId = currReg->physId;
			// delink the intNode
			int id = currInt->val;
			currInt = currInt->next;
			deleteIntNode(id, &liveList);
			// update the availability of the physical register
			int physIndex = physId - 3;
			physStatuses[physIndex] = FREE;
		}
		// otherwise, iterate as normal
		else{
			currInt = currInt->next;
		}
	}
	// Second pass: allocate physical registers to the remaining virtual registers
	currInt = liveList;
	while(currInt != NULL) {
		// obtain current register
		regNode currReg = getRegNode(currInt->val, head);
		// if no physical register has been yet allocated
		if(currReg->status == NONE) {
			// look for the next physical register available
			int index = 0;
			while(index < allocatableRegs) {
				if(physStatuses[index] == FREE) {
					break;
				}
				index += 1;
			}
			// exit on failure if we haven't found any free physical registers
			if(index == allocatableRegs) {
				printf("ERROR in chooseAndAllocate()! Couldn't find free, allocatable physical registers!\n");
				exit(EXIT_FAILURE);
			}
			// set the physID to index + 3 (because register allocation starts at r3)
			currReg->physId = index + 3;
			currReg->status = PHYS;
			// mark the physical register as not currently free
			physStatuses[index] = USED;
		}
		// iterate either way
		currInt = currInt->next;
	}
	*liveListPtr = liveList;
	return;
}

int ascCompLive(const void *in1, const void *in2) {
	// cast the inputs to regNodes
	regNode n1 = *((regNode *) in1);
	regNode n2 = *((regNode *) in2);
	// obtain number of occurrences of each register
	intNode currNode = n1->firstOcc;
	currNode = n2->firstOcc;
	int n1Count = intNodeListLength(n1->firstOcc);
	int n2Count = intNodeListLength(n2->firstOcc);
	// return -1 if first register has fewer occs than second
	if(n1Count < n2Count) {
		return -1;
	}
	// tie-break on live range if same number of occs
	else if(n1Count == n2Count) {
		int n1LiveRange = n1->lastInstr - n1->firstInstr;
		int n2LiveRange = n2->lastInstr - n2->firstInstr;
		// if n1 has longer live range, it comes first.
		if(n1LiveRange > n2LiveRange) {
			return -1;
		}
		// if n1 has shorter live range, it comes after.
		else if(n1LiveRange < n2LiveRange) {
			return 1;
		}
		// if n1 and n2 have same live range, they're tied.
		else {
			return 0;
		}
	}
	// return 1 if first register has more occs than second
	else {
		return 1;
	}
}

void topDownLive(int numRegisters, FILE *file) {
	// First, obtain the linked list of regNodes from the file.
	regNode head = genRegList(file);
	// get the number of virtual registers (excluding r0)
	int numVirtual = regNodeListLength(head);
	// if we have enough physical registers to not need real allocation, give each regNode (besides for r0)
	// a physical register
	if(numRegisters >= numVirtual) {
		uint currId = 3;
		int count = 0;
		regNode currReg = head;
		while(count < numVirtual) {
			if(currReg->id != 0) {
				currReg->status = PHYS;
				currReg->physId = currId;
				currId += 1;
				count += 1;
			}
			currReg = currReg->next;
		}
	}
	// otherwise, perform live-range-dependent algorithm
	else{
		// Iterate through the file, instruction by instruction, and perform the spill and allocation
		// operations accordingly. We only iterate through the file this time for the purpose of counting
		// instructions, not actually reading the input.
		ssize_t read = 0;
		ssize_t len = 0;
		char *currLine = NULL;
		// keep track of current instruction
		int currInstr = 0;
		// number of allocatable registers
		int allocatableRegs = numRegisters - 2;
		// current available offset for spilling
		int currOffset = -4;
		// list of live registers (by ID)
		intNode liveList = NULL;
		// initialize a list of PHYS_STATUS enums that keep track of the availability of allocatable registers
		PHYS_STATUS physStatuses[allocatableRegs];
		int i;
		for(i = 0; i < allocatableRegs; i++) {
			physStatuses[i] = FREE;
		}
		// Let's go to each non-blank line and fetch it.
		while(read = getline(&currLine, &len, file) != -1) {
			// Ignore a blank line or a comment.
			if(strlen(currLine) != 1 && currLine[0] != '/') {
				// spill and allocate for the current line
				chooseAndSpill(currInstr, allocatableRegs, physStatuses, &currOffset, head, &liveList);
				chooseAndAllocate(currInstr, allocatableRegs, physStatuses, head, &liveList);
				// increment the instruction
				currInstr += 1;
			}
			// free the current line's memory, and set the pointer to null
			free(currLine);
			currLine = NULL;
		}
		// Be kind: Rewind (the file pointer)!
		rewind(file);
	}
	// Just like the normal top-down allocator, we go through line-by-line and perform the
	// operations for that given line
	ssize_t read = 0;
	ssize_t len = 0;
	char *currLine = NULL;
	// Let's go to each non-blank line and fetch it. Then use opTD() to process
	// the line and provide the according output.
	while(read = getline(&currLine, &len, file) != -1) {
		// Ignore a blank line or a comment.
		if(strlen(currLine) != 1 && currLine[0] != '/') {
			// perform the operation(s) for this line
			opTD(currLine, head);
		}
		// free the current line's memory, and set the pointer to null
		free(currLine);
		currLine = NULL;
	}
	// Be kind: Rewind (the file pointer)!
	rewind(file);
	// free the structs of the regNode list
	freeRegNode(head);
	return;
}

/* Bottom-up allocation support functions defined here. */

void updateNextInstr(int currInstr, regNode head) {
	regNode currNode = head;
	// iterate through each regNode
	while(currNode != NULL) {
		// for each intNode, iterate through
		intNode currInt = currNode->firstOcc;
		while(currInt != NULL) {
			// if we find an occurrence that >= currInstr, update nextInstr to that occ and break
			if(currInt->val >= currInstr) {
				currNode->nextInstr = currInt->val;
				break;
			}
			// keep iterating
			currInt = currInt->next;
		}
		// if we never found such an intNode, the register is done, so set nextInstr to -1
		if(currInt == NULL) {
			currNode->nextInstr = -1;
		}
		// iterate to the next node
		currNode = currNode->next;
	}
}

int nextComp(const void *in1, const void *in2) {
	// cast the inputs to regNodes
	regNode n1 = *((regNode *) in1);
	regNode n2 = *((regNode *) in2);
	int n1Next = n1->nextInstr;
	int n2Next = n2->nextInstr;
	// return 0 if the registers have the same next instruction (could also mean they're both dead)
	if(n1Next == n2Next) {
		return 0;
	}
	// return -1 if n1 is dead
	else if(n1Next == -1) {
		return -1;
	}
	// return 1 if n2 is dead
	else if(n2Next == -1) {
		return 1;
	}
	// return -1 if n1 comes later than n2
	else if(n1Next > n2Next) {
		return -1;
	}
	// return 1 if n2 comes later than n1
	else{
		return 1;
	}
}

void bottomUp(int numRegisters, FILE *file) {

}


/* main() function receives arguments as described in the assignment spec,
and performs the corresponding allocation algorithm with the given number
of registers. New file is output, line-by-line, to stdout. 

argv has, in order: the number of registers, the */

int main(int argc, char *argv[]) {
	// First: gather information and initialize environment using the arguments.
	// the number of registers requested by the user, passed in the first arg
	int numRegs;
	// the operation type, indicated by a character passed in the second arg
	char typeOp;
	// the file pointer for the requested ILOC file
	FILE *file;
	// Fetch the number of registers from the first argument. Using strtol()
	// because it's a stdlib function that gets the job done.
	numRegs = strtol(argv[1], NULL, 10);
	// Error if the number of registers is less than 2.
	if(numRegs < 2) {
		printf("Error! Invalid number of registers from input: %d\n", numRegs);
		exit(EXIT_FAILURE);
	}
	// Get the type character from typeStr.
	typeOp = argv[2][0];
	// Open up the file pointer to the input file. Read permissions ONLY.
	file = fopen(argv[3], "r");
	// If file-opening operation was unsuccessful, print an error and exit.
	if(file == NULL) {
		printf("Error opening file: %s !\n", argv[3]);
		exit(EXIT_FAILURE);
	}
	// call the according allocation algorithm
	if(typeOp == 's') {
		topDownSimple(numRegs, file);
	}
	else if(typeOp == 't') {
		topDownLive(numRegs, file);
	}
	else if(typeOp == 'b') {
		printf("Requested bottom-down allocator. Not currently implemented.\n");
		return 0;
	}
	else {
		printf("Error in main()! Invalid allocator type input: %c\n", typeOp);
		exit(EXIT_FAILURE);
	}

	close(file);

	return 1;


}