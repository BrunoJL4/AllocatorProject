// Homework 1 #3 part b, with MAX_LIVE considerations
// load base address into machine register
loadI 1024 => r0
loadI 1 => r1
loadI 2 => r2
// spill code for previous r3
// "old" r3 == r0, 0;
subI r2, 4 => r4
storeAI r4 => r0, 0
// resume from old statement 4... can use r2 now
// "old" r1 == r1; "old" r4 == r2
add r1, r2 => r2
// statement 5
// "old" r1 == r1; "old" r4 == r2; "old" r5 == r3
addI r2, 1 => r3
// statement 6
// "old" r1 == r1; "old" r4 == r2; "old" r5 == r3;
// "old" r6 == r0, 4
loadAI r0, 0 => r4
mult r4, r3 => r5
storeAI r5 => r0, 4
// statement 7
// "old" r1 == r1; "old" r4 == r2; "old" r5 == r3;
// "old" r6 == r0, 4; "old" r7 == r0, 8
loadAI r0, 4 => r4
sub r3, r4 => r5
storeAI r5 => r0, 8
// statement 8... can use r3 now (previously storing r5)
// "old" r1 == r1; "old" r4 == r2; "old" r6 == r0, 4;
// "old" r7 == r0, 8; "old" r8 == r3
add r2, r3 => r3
// statement 9... can use r3 now (previously storing r8)
// and can use r2 now (previously storing r4)
// "old" r1 == r1; "old" r6 == 0, 4; "old" r7 == r0, 8;
// "old" r9 == r2;
loadAI r0, 8 => r4
add r3, r4 => r2
// statement 10... can use whatever registers we want besides r0
// "old" r1 == r1; "old" r9 == r2; "old" r10 == r3 AND r0, 12
add r2, r1 => r3
storeAI r3 => r0, 12
// output r10
outputAI r0, 12