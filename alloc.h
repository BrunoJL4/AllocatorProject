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
or in a physical register. NONE if the corresponding struct was just initialized. */
typedef enum REG_STATUS_ENUM {
	MEM = 0,
	PHYS = 1,
	NONE = 2,
	DEAD = 3,
	PHYS_ACTIVE_INPUT = 4,
	MEM_ACTIVE_INPUT = 5,
	PHYS_ACTIVE_OUTPUT = 6,
	MEM_ACTIVE_OUTPUT = 7
} REG_STATUS;

/* The enum type for top-down operations- simple or "live-considering". */
typedef enum TD_TYPE_ENUM {
	SIMPLE = 0,
	LIVE = 1,
	BOTTOM = 2
} TD_TYPE;

/* The enum type for physical register availability. Used in live-range dependent top-down allocation.*/
typedef enum PHYS_STATUS_ENUM {
	USED = 0,
	FREE = 1
} PHYS_STATUS;

/* The enum type indicating whether a register is an input or output. */
typede enum REG_TYPE_ENUM {
	IN = 0,
	OUT = 1
} REG_TYPE;

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
	// 9001 by default.
	int offset;
	// the next regNode in the linked list. NULL by default.
	struct registerNode *next;
	// the first instruction this register is live (present) in
	int firstInstr;
	// the last instruction this register is live in 
	int lastInstr;
	// the next instruction this register is live in (bottom-up only)
	int nextUse;
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

/* Adds an intNode to the end of the list, which is pointed to by intHeadPtr. */
void addIntNode(int val, intNode *intHeadPtr);

/* Simple top-down exclusive functions below. */

/* Performs top-down allocation given the number of registers from the user, and the
file pointer from their file. Output is given to stdout. */
void topDownSimple(int numRegisters, FILE *file);

/* Performs the given operations for simple top-down allocation, given the current line.
This includes spilling, fetching, and standard output. */
void opTD(char *currLine, regNode head);

/* Compares the two regNodes such that a qsort()'ed list will be set in descending order
of occurrences. Returns -1 if n1 has more occurrences than n2, 0 if they're the same,
1 if n1 has fewer occurrences than n2. */
int descComp(const void *in1, const void *in2);


/* Lecture top-down exclusive functions below. */

/* Given an instruction number, this function goes through the list of regNodes and adds them to the liveList
if they're not already there. It then, if necessary, decides which registers to spill at that instruction,
and changes their status/location accordingly. Finally, it removes the spilled registers from the list. 

If there are no allocatable registers available, this function will spill every register on each line.*/
void chooseAndSpill(int instr, int allocatableRegs, PHYS_STATUS *physStatuses, int *currOffset, regNode head, intNode *liveListPtr);

/* This function assumes that the scanning/liveList operations/spilling from chooseAndSpill have already occurred.

Takes an instruction number, the number of allocatable registers, an enum array indicating (for a given index)
the status of a physical register, the regNode list, and a pointer to liveList. 

First goes through liveList and checks for any virtual registers that, at this instruction, are no longer live.
For these virtual registers, we remove them from liveList and set the according index in physStatuses to FREE.
Then we do another pass and, for each one whose physStatus is FREE, delink it from liveList.

*physStatuses's index for the register it references corresponds to: physStatuses[0] indicates the status of r3.
physStatuses[1] for r4, and so on. If we have NO allocatable registers, the array will be NULL, and allocatableRegs
will be 0. Return instantly in that case.*/
void chooseAndAllocate(int instr, int allocatableRegs, PHYS_STATUS *physStatuses, regNode head, intNode *liveListPtr);

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


/* Bottom-up exclusive functions below. */

/* Updates the nextInstr member for every regNode in the list indicated by head. Assigns nextInstr to -1
if there are no occurrences left after the current instruction. */
void updateNextInstr(int currInstr, regNode head);

/* Compares two regNodes to determine order of eviction (spilling). If in1's next occurrence equals in2's next
occurrence, return 0. If in1's next occurrence is greater than in2's next occurrence, OR if in1's next occurrence
is -1, then return -1. If in1's next occurrence is less than in2's next occurrence, OR if in2's next occurrence is -1,
return 1. */
int nextComp(const void *in1, const void *in2);

/* Updates the target virtual register's regNode with the given status. */
void setActiveStatus(int reg, regNode head, REG_TYPE type);

/* Updates the liveList given the registers that are ACTIVE on a line, and the type of the operation. 
Also updates the ACTIVE status of those registers' regNodes.*/
void updateLiveListBottom(intNode liveList, regNode head, OP_TYPE op, int opReg1, int opReg2, int opReg3);

/* Spills and fetches registers as necessary for the current operation, using the next-occurrence format. This includes changing
the properties of the registers and providing the stdout output for fetch/spill operations.*/
void spillFetchAssignBU(intNode liveList, regNode head, regNode *sortedRegArr, PHYS_STATUS *physStatuses, int &currOffsetPtr);

/* Performs the actual operational output for a given line, without changing the properties of the registers involved. */
void outputBU(regNode head, OP_TYPE op, int opReg1, int opReg2, int opReg3, int constant);

/* Performs bottom-up allocation given the number of registers from the user, and the
file pointer from their file. Output is given to stdout. */
void bottomUp(int numRegisters, FILE *file);

#endif