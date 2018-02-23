// File:	my_pthread_t.h
// Author:	Bruno J. Lucarelli
// Date:	02-22-17
// username of iLab: bjl145
// iLab Server: man.cs.rutgers.edu

#include "alloc.h"

/* General support functions defined here. */

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

/* Top-down allocation (simple) support functions defined here. */

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
//	printf("numRegs is: %d\n", numRegs);
//	printf("typeOp is: %c\n", typeOp);
//  printf("filename is: %s\n", argv[3]);
	// Open up the file pointer to the input file. Read permissions ONLY.
	file = fopen(argv[3], "r");
	// If file-opening operation was unsuccessful, print an error and exit.
	if(file == NULL) {
		printf("Error opening file: %s !\n", argv[3]);
		exit(EXIT_FAILURE);
	}

	// Getting started: let's go through the file and print every line that isn't
	// a blank space, or that isn't a comment. Go until EOF.
	ssize_t read = 0;
	ssize_t len = 0;
	char *currLine = NULL;
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
			printf("enum value: %d\n", op);
			printf("opReg1: %d\n", opReg1);
			printf("opReg2: %d\n", opReg2);
			printf("opReg3: %d\n", opReg3);
			printf("opConst: %d\n", opConst);
		}
		// free the current line's memory, and set the pointer to null
		free(currLine);
		currLine = NULL;
	}
	rewind(file);
	close(file);

	return 1;


}