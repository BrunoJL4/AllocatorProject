// Homework 1 problem #1, register-register model
//
// Assign STATIC_AREA_ADDRESS to r0 by default;
loadI 1024 => r0
// INPUT VARIABLE GOES HERE; a == r1;
loadI 5 => r1
// spill a; r0, 0
storeAI r1 => r0, 0
// result == r2;
loadI 1 => r2
// spill result; r0, 4
storeAI r2 => r0, 4
// Define LOOP
LOOP:
	// load a to r1
	loadAI r0, 0 => r1
	// load 1 to r2
	loadI 1 => r2
	// compare and store comparison in r2
	cmp_GT r1, r2 => r2
	cbr r2, GT, LT
// Define GT (a > 1)
GT:
	// load a to r1
	loadAI r0, 0 => r1
	// load result to r2
	loadAI r0, 4 => r2
	// multiply r1 and r2, store result to r2 (result)
	mult r1, r2 => r2
	// store result in memory (result)
	storeAI r2 => r0, 4
	// subtract 1 from a
	subI r1, 1 => r1
	// update a in memory
	storeAI r1 => r0, 0
	// jump to LOOP
	br LOOP
// Define LT (a <= 1)
LT:
	// output result (r0, 4)
	outputAI r0, 4
