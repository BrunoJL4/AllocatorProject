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
	LOAD = 1,
	STORE = 2,
	ADD = 3,
	SUB = 4,
	MULT = 5,
	LSHIFT = 6,
	RSHIFT = 7,
	OUTPUT = 8,
	DEFAULT = 9
} OP_TYPE;

/* The enum types that tell us whether a virtual register is currently spilled in memory,
or in a physical register. DEFAULT if the corresponding struct was just initialized. */
typedef enum REG_STATUS_ENUM {
	MEM = 0,
	PHYS = 1,
	NONE = 2
} REG_STATUS;

/* The enum type for top-down operations- simple or "live-considering". */
typedef enum TD_TYPE_ENUM {
	SIMPLE = 0,
	LIVE = 1
} TD_TYPE;

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
	// the first instruction this register is live (present) in
	int firstInstr;
	// the last instruction this register is live in 
	int lastInstr;
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

/* This function takes a file pointer, and returns a linked list of regNodes. The regNodes
have their occurrence lists populated according to the ILOC instructions in the file.
This essentially gathers all of the information we need for top-down and bottom-up allocation
before scrolling down a set of instructions:

a) Top-down allocation needs the list of occurrences for live ranges, number of
occurrences, and MAXLIVE measurements.

b) Bottom-up allocation needs the list of occurrences for the deterimination of the next
occurrence of a given register, from a given instruction.

*/
regNode genRegList(FILE *file);

/* This function adds a regNode to a linked list, if it doesn't already exist. */
void addReg(uint id, regNode head);

/* This function adds an intNode to a regNode's linked list, if it's not already present
(and if the occurrence exists). This marks a new occurrence of the virtual register in the ILOC
instructions.

Attempts will regularly be made to add duplicate occurrences, as registers will often
appear in the same line.*/
void addOccToReg(int val, uint id, regNode);

/* Debugging function. Prints out the contents of a regNode. */
void printRegNode(regNode node);

/* Debugging function. Runs through a list of regNodes and prints their contents,
including the occurrences present in each. */
void printRegList(regNode head);

/* Returns -1 if the target intNode doesn't exist, 1 if it does. */
int intNodeExists(int target, intNode head);

/* Frees a list of intNodes. */
void freeIntNode(intNode head);

/* Returns a regNode if one matching the target ID exists. Returns NULL if it doesn't. */
regNode getRegNode(uint id, regNode head);

/* Performs the spill code given a virtual register ID, the feasible register ID
that its value is stored in, and the head of the regNode list. Also changes the
register's status and location members accordingly. */
void spillReg(uint targetId, uint feasId, regNode head);

/* Performs the fetching spill code given a virtual register ID, the feasible register ID
that its value will be stored in, and the head of the regNode list. Also changes the
register's status and location members accordingly (physId set to 999, default). */
void fetchReg(uint targetId, uint feasId, regNode head);

/* Given a linked list of regNodes, returns a dynamically-allocated array with the regNodes 
sorted in descending order of number of occurrences (besides r0). Nodes will also be sorted
by live range as a tie-breaker if the LIVE flag is provided instead of SIMPLE. This means that for
x virtual registers including r0, the length of the array will be x, with ret[x] == NULL. 
Note that the array returned from here must be freed.*/
regNode *sortedRegArr(regNode head, TD_TYPE type);

/* Returns the length of a list of intNodes. */
int intNodeListLength(intNode head);

/* Returns the length of a list of regNodes. */
int regNodeListLength(regNode head);

/* Deletes the target intNode from the list. If applicable, changes headPtr's referenced intNode
(if the target is at head). */
void deleteIntNode(int target, intNode *headPtr);

/* Given an instruction number, this function goes through the list of regNodes and adds them to the liveList
if they're not already there. It then, if necessary, decides which registers to spill at that instruction,
and changes their status/location accordingly. Finally, it removes the spilled registers from the list. */
void chooseAndSpill(int instr, regNode head, intNode liveList);

/* Adds an intNode to the end of the list, which is pointed to by intHeadPtr. */
void addIntNode(int val, intNode *intHeadPtr);

/* Simple top-down exclusive functions below. */

/* Performs top-down allocation given the number of registers from the user, and the
file pointer from their file. Output is given to stdout. */
void topDownSimple(int numRegisters, FILE *file);

/* Performs the given operations for simple top-down allocation, given the current line.
This includes spilling, fetching, and standard output. */
void opSimpleTD(char *currLine, regNode head);

/* Compares the two regNodes such that a qsort()'ed list will be set in descending order
of occurrences. Returns -1 if n1 has more occurrences than n2, 0 if they're the same,
1 if n1 has fewer occurrences than n2. */
int descComp(const void *in1, const void *in2);


/* Lecture top-down exclusive functions below. */

/* Compares the two regNodes such that a qsort()'ed list will be set in ascending order
of number of occurrences. Live range will be used as a tie-breaker- the longer live range
will go earlier in the list.

This is used in the lecture top-down allocation, because we choose to evict registers in such
an order.*/
int ascCompLive(const void *in1, const void *in2);

/* Performs the top-down allocation from lecture. Only the number of physical registers
and the file pointer. Output is given to stdout. 

Takes each line of input, the regNode list from the file, keeps track of the current instruction, 
passes a sorted array of registers by the lecture heuristic, and keeps track of which virtual registers are
live. Modifies the list of liveRegs accordingly, and the status/location properties of the regNodes linked
to input head. */
void topDownLive(int numRegs, FILE *file);

/* Performs the actual operations for lecture top-down allocation. This includes:

1. Parsing the input for operation type/virtual register ID's, just like simple top-down.
2. Determining which operations are live at this line, and which aren't. 

*/
void opLiveTD(char *currLine, regNode head, uint currInstr, regNode* sortedRegs, intNode liveRegs,
	int allocRegs);


/* Bottom-up exclusive functions below. */


#endif