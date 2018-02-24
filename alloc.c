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
	newNode->offset = -9001;
	newNode->next = NULL;
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
	

void addOcc(int occ, uint id, regNode head) {
	// First, obtain the regNode corresponding to parameter id, if any.
	regNode currReg = head;
	while(currReg != NULL) {
		if(currReg->id == id) {
			break;
		}
		currReg = currReg->next;
	}
	// If target register not present, return.
	if(currReg == NULL) {
		printf("Error in addOcc()! Register r%d not present, but attempting to add occurrence at line %d\n",
			id, occ);
		exit(EXIT_FAILURE);
	}
	// Otherwise, continue on and attempt to add the occurrence.
	intNode newNode = createIntNode(occ);
	// First case: if the regNode has no occurrences, add a newly-allocated node in.
	intNode currNode = currReg->firstOcc;
	if(currNode == NULL) {
		currReg->firstOcc = newNode;
//		printf("Successfully added occ %d to r%d!\n", occ, id);
		return;
	}
	// Normal case: first node is occupied and not the same as the input. Iterate through the list. 
	// If the occurrence isn't present, add it to the very end.
	while(currNode != NULL) {
		// Return if we've found the occurrence already present.
		if(currNode->val == occ) {
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
//	printf("Successfully added occ %d to r%d!\n", occ, id);
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
//	printf("Successfully added r%d to list!\n", id);
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
//			printf("Instruction: %d\n", currInstr);
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
//				printf("loadI operation.\n");
				// next value would be a constant.
				opConst = nextNum(currLine, &currIndex);
				// following that, a register.
				opReg1 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "loadAI") == 0) {
//				printf("loadAI operation.\n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, a constant.
				opConst = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg2 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "load") == 0) {
//				printf("load operation.\n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "store") == 0) {
//				printf("store operation.\n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "storeAI") == 0) {
//				printf("storeAI operation.\n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, a constant.
				opConst = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "add") == 0) {
//				printf("add operation.\n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "sub") == 0) {
//				printf("sub operation.\n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register. 
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "mult") == 0) {
//				printf("mult operation. \n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "lshift") == 0) {
//				printf("lshift operation.\n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "rshift") == 0) {
//				printf("rshift operation.\n");
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "output") == 0) {
//				printf("output operation.\n");
				// value would be a constant.
				opConst = nextNum(currLine, &currIndex);
			}
			else{
				printf("ERROR! No valid operation provided.\n");
				exit(EXIT_FAILURE);
			}
//			printf("opReg1: %d\n", opReg1);
//			printf("opReg2: %d\n", opReg2);
//			printf("opReg3: %d\n", opReg3);
//			printf("opConst: %d\n", opConst);
			// FIRST CASE: if firstNode is NULL, set it to the first of the registers
			// that appears.
			if(firstNode == NULL) {
				if(opReg1 != -1) {
					firstNode = createRegNode(opReg1);
//					printf("Succesfully added r%d as first register!\n", opReg1);
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
				addOcc(currInstr, opReg1, firstNode);
			}
			if(opReg2 != -1) {
				addReg(opReg2, firstNode);
				addOcc(currInstr, opReg2, firstNode);
			}
			if(opReg3 != -1) {
				addReg(opReg3, firstNode);
				addOcc(currInstr, opReg3, firstNode);
			}
			// increment the instruction number, since we've successfully finished a valid instruction.
			currInstr += 1;
		}
		// free the current line's memory, and set the pointer to null
		free(currLine);
		currLine = NULL;
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

void spillReg(uint targetId, uint feasId, regNode head) {
	// obtain the regNode instance we want to spill/modify
	regNode targetNode = getRegNode(targetId, head);
	if(targetNode == NULL) {
		printf("Error in spillReg! Target %d doesn't exist!\n", targetId);
		exit(EXIT_FAILURE);
	}
	// obtain its offset
	int offset = targetNode->offset;
	// print the spill operation to standard output
	fprintf(stdout, "storeAI r%d => r0, %d\n", feasId, offset);
	// modify the target node's status to in memory
	targetNode->status = MEM;
	// modify the target node's physId to 999 (default)
	targetNode->physId = 999;
	return;
}

void fetchReg(uint targetId, uint feasId, regNode head) {
	// obtain the regNode instance we want to fetch/modify
	regNode targetNode = getRegNode(targetId, head);
	if(targetNode == NULL) {
		printf("Error in fetchReg! Target %d doesn't exist!\n", targetId);
		exit(EXIT_FAILURE);
	}
	// obtain its offset
	int offset = targetNode->offset;
	// print the loadAI operation to standard output
	fprintf(stdout, "loadAI r0, %d => r%d\n", offset, feasId);
	// modify the target node's status to in-phys
	targetNode->status = PHYS;
	// modify the target node's physId to that of the feasible register
	targetNode->physId = feasId;
	return;
}

int descComp(const void *in1, const void *in2) {
	// cast the inputs to regNodes
	regNode n1 = *((regNode *) in1);
	regNode n2 = *((regNode *) in2);
	// obtain number of occurrences of each register
	int n1Count = 0;
	int n2Count = 0;
	intNode currNode = n1->firstOcc;
	while(currNode != NULL) {
		n1Count += 1;
		currNode = currNode->next;
	}
	currNode = n2->firstOcc;
	while(currNode != NULL) {
		n2Count += 1;
		currNode = currNode->next;
	}
//	printf("comparing r%d and r%d\n", n1->id, n2->id);
//	printf("number of occs in r%d: %d\n", n1->id, n1Count);
//	printf("number of occs in r%d: %d\n", n2->id, n2Count);
	// return -1 if first register has more occs than second
	if(n1Count > n2Count) {
//		printf("r%d > r%d!\n\n", n1->id, n2->id);
		return -1;
	}
	// return 0 if they have same number of occs
	else if(n1Count == n2Count) {
//		printf("r%d == r%d!\n\n", n1->id, n2->id);
		return 0;
	}
	// return 1 if first register has fewer occs than second
	else {
//		printf("r%d < r%d!\n\n", n1->id, n2->id);
		return 1;
	}
}

regNode *sortedRegArr(regNode head) {
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
	// Sort midArr using qsort() and descComp.
	qsort((void *) midArr, listLength - 1, sizeof(regNode), descComp);
	// Transfer midArr to a dynamically-allocated return array.
	regNode *retArr = (regNode *) malloc(listLength * sizeof(regNode));
	retArr[listLength-1] = NULL;
	int i;
	for(i = 0; i < listLength-1; i++) {
		retArr[i] = midArr[i];
	}
	
	/*
	// debugging: print contents of retArr:
	printf("printing contents of retArr: \n");
	for(i = 0; i < listLength; i++) {
		// obtain number of occurrences
		if(retArr[i] != NULL) {
			printf("register id: %d\n", retArr[i]->id);
			intNode currOcc = retArr[i]->firstOcc;
			int len = 0;
			while(currOcc != NULL) {
				len += 1;
				currOcc = currOcc->next;
			}
			printf("number of occs: %d\n\n", len);
		}
		else {
			printf("retArr[%d] is NULL!\n", i);
		}
	}
	*/
	
	return retArr;
}

void opSimpleTD(char *currLine, regNode head) {
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
	}
	else if(strcmp(opString, "loadAI") == 0) {
		// loadAI r0, 4 => r3
		// next value would be a register.
		uint inReg = nextNum(currLine, &currIndex);
		// following that, a constant.
		int constant = nextNum(currLine, &currIndex);
		// finally, another register.
		uint outReg = nextNum(currLine, &currIndex);
	}
	else if(strcmp(opString, "load") == 0) {
		// load r1 => r2 means: load MEM[r1] into r2
		// next value would be a register.
		uint inReg = nextNum(currLine, &currIndex);
		// following that, another register.
		uint outReg = nextNum(currLine, &currIndex);
	}
	else if(strcmp(opString, "store") == 0) {
		// store r1 => r2 means: store r1 into MEM[r2]
		// next value would be a register.
		uint inReg = nextNum(currLine, &currIndex);
		// following that, another register.
		uint outReg = nextNum(currLine, &currIndex);
	}
	else if(strcmp(opString, "storeAI") == 0) {
		// storeAI r1 => r0, 4
		// next value would be a register.
		uint inReg = nextNum(currLine, &currIndex);
		// following that, another register.
		uint outReg = nextNum(currLine, &currIndex);
		// finally, a constant.
		int constant = nextNum(currLine, &currIndex);
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
	}
	else if(strcmp(opString, "output") == 0) {
		// output 1028
		// value would be a constant.
		int constant = nextNum(currLine, &currIndex);
	}
	else{
		printf("ERROR! No valid operation provided.\n");
		exit(EXIT_FAILURE);
	}
}




/* Top-down allocation (simple) support functions defined here. */

void topDownSimple(int numRegisters, FILE *file) {
	// First, obtain the linked list of regNodes from the file.
	regNode head = genRegList(file);
	// Next, obtain a dynamically-allocated array of regNodes that's sorted by
	// descending order of occurrences.
	regNode *sortedRegs = sortedRegArr(head);
	// Get the number of allocatable registers (if any) by subtracting 2 (for the feasible
	// registers) from numRegisters.
	int availableRegs = numRegisters - 2;
	// Start allocating physical registers at r3.
	uint currId = 3; 
	uint index = 0;
	regNode currReg = sortedRegs[0];
	// Allocate as many physical registers as we have available for such, until we
	// either run out of physical registers or virtual registers (in sortedRegs).
	while(availableRegs > 0 && currReg != NULL) {
		// Give the currId as a physically-allocated space to the next virtual register
		// in line, and change its status.
		currReg = sortedRegs[index];
		currReg->status = PHYS;
		currReg->physId = currId;
		index += 1;
		currId += 1;
		availableRegs -= 1;
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
	/*
	// debugging: print out the contents of the regNode list itself.
	printf("printing out all of the registers in the linked list!\n");
	printRegList(head);
	printf("\n\n");
	// debugging: print the contents of sortedRegs.
	printf("Printing out the sorted register list!\n");
	currReg = sortedRegs[0];
	index = 0;
	while(currReg != NULL) {
		printRegNode(currReg);
		printf("\n");
		index += 1;
		currReg = sortedRegs[index];
	} */
	// Now that the physical registers have been allocated (if any), we provide output
	// contingent with what we find line-by-line.
	// Getting started: let's go through the file and perform top-down operations on
	// every non-blank line.
	ssize_t read = 0;
	ssize_t len = 0;
	char *currLine = NULL;
	// Let's go to each non-blank line and fetch it. Then use opSimpleTD() to process
	// the line and provide the according output.
	int currInstr = 0;
	while(read = getline(&currLine, &len, file) != -1) {
		// Ignore a blank line or a comment.
		if(strlen(currLine) != 1 && currLine[0] != '/') {
			// perform the operation(s) for this line
			opSimpleTD(currLine, head);
			// increment the current instruction
			currInstr += 1;
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


/* Top-down allocation (lecture) support functions defined here. */

/* Bottom-up allocation support functions defined here. */





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
		printf("Requested complex top-down allocator. Not currently implemented.\n");
		return 0;
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


/* SKELETON CODE FOR TRAVERSING AN ILOC FILE AND PARSING OPS LINE-BY-LINE:*/
/*
    // Getting started: let's go through the file and print every line that isn't
	// a blank space, or that isn't a comment. Go until EOF.
	ssize_t read = 0;
	ssize_t len = 0;
	char *currLine = NULL;
	// These variables store, respectively, the first regNode in the list, and
	// the current/last regNode currently in the list.
	regNode firstNode = NULL;
	regNode currNode = NULL;
	// Let's go to each non-blank line and obtain the type of the operation, plus
	// the (up to three) registers involved. Registers will be obtained in order
	// of appearance, and a register can appear more than once in an operation;
	// Current valid instruction in ILOC.
	int currInstr = 0;
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
			// Can now set the enum for the current operation type.
			OP_TYPE op = DEFAULT;
			// Any operation may have up to 3 registers involved (duplicates allowed),
			// and one constant value. 
			int opReg1 = -1;
			int opReg2 = -1;
			int opReg3 = -1;
			int opConst = -1;
			if(strcmp(opString, "loadI") == 0) {
				printf("loadI operation.\n");
				op = LOADI;
				// next value would be a constant.
				opConst = nextNum(currLine, &currIndex);
				// following that, a register.
				opReg1 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "loadAI") == 0) {
				printf("loadAI operation.\n");
				op = LOADAI;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, a constant.
				opConst = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg2 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "load") == 0) {
				printf("load operation.\n");
				op = LOAD;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "store") == 0) {
				printf("store operation.\n");
				op = STORE;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "storeAI") == 0) {
				printf("storeAI operation.\n");
				op = STOREAI;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, a constant.
				opConst = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "add") == 0) {
				printf("add operation.\n");
				op = ADD;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "sub") == 0) {
				printf("sub operation.\n");
				op = SUB;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register. 
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "mult") == 0) {
				printf("mult operation. \n");
				op = MULT;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "lshift") == 0) {
				printf("lshift operation.\n");
				op = LSHIFT;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "rshift") == 0) {
				printf("rshift operation.\n");
				op = RSHIFT;
				// next value would be a register.
				opReg1 = nextNum(currLine, &currIndex);
				// following that, another register.
				opReg2 = nextNum(currLine, &currIndex);
				// finally, another register.
				opReg3 = nextNum(currLine, &currIndex);
			}
			else if(strcmp(opString, "output") == 0) {
				printf("output operation.\n");
				op = OUTPUT;
				// value would be a constant.
				opConst = nextNum(currLine, &currIndex);
			}
			else{
				printf("ERROR! No valid operation provided.\n");
				exit(EXIT_FAILURE);
			}
			printf("current instruction: %d\n", currInstr);
			printf("enum value: %d\n", op);
			printf("opReg1: %d\n", opReg1);
			printf("opReg2: %d\n", opReg2);
			printf("opReg3: %d\n", opReg3);
			printf("opConst: %d\n", opConst);
			// increment the current instruction
			currInstr += 1;
		}
		// free the current line's memory, and set the pointer to null
		free(currLine);
		currLine = NULL;
	}
	// Be kind: Rewind (the file pointer)!
	rewind(file);
	*/