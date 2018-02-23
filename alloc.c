// File:	my_pthread_t.h
// Author:	Bruno J. Lucarelli
// Date:	02-22-17
// username of iLab: bjl145
// iLab Server: man.cs.rutgers.edu

#include "alloc.h"

/* General support functions defined here. */

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
	/*
	while(read = getline(&currLine, &len, file) != -1) {
		// If a line is blank (length 1) or starts with a slash,
		// ignore it. Blank lines are "length 1" for the purposes
		// of well-formed test cases.
		if(strlen(currLine) != 1 && currLine[0] != '/') {
			printf("Retrieved line of size: %d\n", strlen(currLine));
			printf("%s", currLine);
			printf("currLine[1] is: %c\n", currLine[1]);
		}
		// free the current line's memory, and set the pointer to null
		free(currLine);
		currLine = NULL;
	}
	currLine = NULL;
	read = 0;
	rewind(file);
	*/
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
			lastIndex = currIndex - 1;
			// The length of the actual operation string will be 1 more than the
			// difference between the two indexes. Copy the operation string
			// over to a null-terminated stack buffer, to prepare for comparison.
			uint opLength = lastIndex - firstIndex + 1;
			char opString[opLength + 1];
			opString[opLength] = '\0';
			strncpy(opString, &(currLine[firstIndex]), opLength);
			// Can now set the enum for the current operation type.
			OP_TYPE op = DEFAULT;
			// Using strcmp() because for "store" vs "storeAI" instructions,
			// "store" will lose. strncmp() would stop at the end of the shorter string
			// and consider them equal.
			if(strcmp(opString, "loadI") == 0) {
				printf("loadI operation.\n");
				op = LOADI;
			}
			else if(strcmp(opString, "loadAI") == 0) {
				printf("loadAI operation.\n");
				op = LOADAI;
			}
			else if(strcmp(opString, "load") == 0) {
				printf("load operation.\n");
				op = LOAD;
			}
			else if(strcmp(opString, "store") == 0) {
				printf("store operation.\n");
				op = STORE;
			}
			else if(strcmp(opString, "storeAI") == 0) {
				printf("storeAI operation.\n");
				op = STOREAI;
			}
			else if(strcmp(opString, "add") == 0) {
				printf("add operation.\n");
				op = ADD;
			}
			else if(strcmp(opString, "sub") == 0) {
				printf("sub operation.\n");
				op = SUB;
			}
			else if(strcmp(opString, "mult") == 0) {
				printf("mult operation. \n");
				op = MULT;
			}
			else if(strcmp(opString, "lshift") == 0) {
				printf("lshift operation.\n");
				op = LSHIFT;
			}
			else if(strcmp(opString, "rshift") == 0) {
				printf("rshift operation.\n");
				op = RSHIFT;
			}
			else if(strcmp(opString, "output") == 0) {
				printf("output operation.\n");
				op = OUTPUT;
			}
			else{
				printf("ERROR! No valid operation provided.\n");
				exit(EXIT_FAILURE);
			}
			
		}
	}

	return 1;


}