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

/* The enum types for the different ILOC operations that can be found in a test block. */
enum OP_TYPE {
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
	OUTPUT = 10
};

/* The enum types that tell us whether a virtual register is currently spilled in memory,
or in a physical register. */
enum REG_STATUS {
	MEM = 0,
	PHYS = 1
};

/* End enum definitions. */



#endif