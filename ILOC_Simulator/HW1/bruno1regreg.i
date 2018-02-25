// Homework 1 problem #1, register-register model
//
// Assign STATIC_AREA_ADDRESS to r0 by default;
loadI 1024 => r0
// INPUT VALUE GOES HERE; r1 == a
loadI 5 => r1
// r2 == result
loadI 1 => r2
// r3 == 1 (for comparisons);
loadI 1 => r3
// define LOOP
// compare r1 (a) and r3 (1), store result in r4;
// store results of comparison to r4;
// if r4 is true (a > 1), go to GT; else go to LT;
LOOP:
	cmp_GT r1, r3 => r4
	cbr r4, GT, LT
// define GT, or case where a > 1;
// multiply result (r2) and a (r1) into r2's space,
// then subtract 1 from a (r1);
// jump back to loop;
GT:
	mult r2, r1 => r2
	subI r1, 1 => r1
	br LOOP
// define LE, or case where a <= 1 (output result, etc)
// store "result" (r2) in memory (r0, 0) and then output
LT:
	storeAI r2 => r0, 0
	outputAI r0, 0