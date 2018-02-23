// File:	my_pthread_t.h
// Author:	Bruno J. Lucarelli
// Date:	02-22-17
// username of iLab: bjl145
// iLab Server: man.cs.rutgers.edu

/* This header file defines the functions used for the allocator
program. There will be one section for shared data structures
and functions, and then another section for functions exclusive
to each allocator (when applicable).

*/
#ifndef ALLOC_H
#define ALLOC_H

// Including standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

/* Enum definitions below. */

/* The enum types for the different ILOC operations that can be found in a test block. 
These will be used in the support function that provides the operation type
and register ID's (when applicable).*/
typedef enum OP_TYPE_ENUM {
	LOADI = 0,
	LOADAI = 1,
	LOAD = 2,
	STORE = 3,
	STOREAI = 4,
	ADD = 5,
	SUB = 6,
	MULT = 7,
	LSHIFT = 8,
	RSHIFT = 9,
	OUTPUT = 10,
	DEFAULT = 11
} OP_TYPE;

/* The enum types that tell us whether a virtual register is currently spilled in memory,
or in a physical register. */
enum REG_STATUS {
	MEM = 0,
	PHYS = 1
};

/* End enum definitions. */

/* General support functions included below. */

/* This function takes an input string and a pointer to an index. It moves from that current
index to the next numeric value, and returns that value. The function also returns the index
following the end of the next numeric value, which could be a nextline. 

NOTE: Function assumes that currIndexPtr stores an index such that it immediately follows either
a register number or a constant in an ILOC instruction. In no properly-formed ILOC code will two
input/output parameters be lumped together without some spaces/non-numeric symbols.

*/
int nextNum(char *line, int *currIndexPtr);





#endif