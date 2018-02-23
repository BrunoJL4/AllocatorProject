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
	ssize_t read;
	ssize_t len = 0;
	char *currLine = NULL;
	while(read = getline(&currLine, &len, file) != -1) {
		// If a line is blank (length 1) or starts with a slash,
		// ignore it.
		if(strlen(currLine) != 1 && currLine[0] != '/') {
			printf("Retrieved line of size: %d\n", strlen(currLine));
			printf("%s", currLine);
			printf("currLine[1] is: %c\n", currLine[1]);
		}
		// free the current line's memory, and set the pointer to null
		free(currLine);
		currLine = NULL;
	}
	rewind(file);

	return 1;


}