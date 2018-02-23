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
or in a physical register. DEFAULT if the corresponding struct was just initialized. */
typedef enum REG_STATUS_ENUM {
	MEM = 0,
	PHYS = 1,
	NONE = 2
} REG_STATUS;

/* End enum definitions. */

/* General struct definitions included below. */

/* This struct functions as a barebones int node. Used in registerNode to store
linked lists of occurrences. */
typedef struct integerNode {
	// the int stored in this node. default provided in constructor.
	int val;
	// the next intNode in the list. NULL by default.
	struct integerNode *next;
} *intNode;

/* This struct stores information about virtual registers, given their appearances
in original ILOC instructions and their current state in the allocator. These are
stored in linked lists for ease of implementation. */
typedef struct registerNode {
	// the virtual ID of the register, as it appears in original ILOC instructions.
	// default provided in constructor.
	uint id;
	// the current status of the register... if it's in memory (spilled), or in
	// a physical register. DEFAULT by... default.
	REG_STATUS status;
	// the linked list of occurrences of this virtual register in the ILOC code.
	// NULL by default.
	intNode firstOcc;
	// the ID of the current physical register this is stored in, if applicable.
	// 999 by default.
	uint physId;
	// the current offset of this register's data from r0, if applicable.
	// -9001 by default.
	int offset;
	// the next regNode in the linked list. NULL by default.
	struct registerNode *next;
} *regNode;



/* General support functions included below. */

/* Given an ID this function allocates memory for, initializes, and returns a pointer
to a corresponding registerNode. */
regNode createRegNode(uint id);

/* Given an int value this function allocates memory for, initializes, and returns
a pointer to a corresponding integerNode. */
intNode createIntNode(int value);

/* Frees the requested regNode, and all of its referenced intNodes. */
void freeRegNode(regNode input);



/* This function takes an input string and a pointer to an index. It moves from that current
index to the next numeric value, and returns that value. The function also returns the index
following the end of the next numeric value, which could be a nextline. 

NOTE: Function assumes that currIndexPtr stores an index such that it immediately follows either
a register number or a constant in an ILOC instruction. In no properly-formed ILOC code will two
input/output parameters be lumped together without some spaces/non-numeric symbols.

*/
int nextNum(char *line, int *currIndexPtr);





#endif