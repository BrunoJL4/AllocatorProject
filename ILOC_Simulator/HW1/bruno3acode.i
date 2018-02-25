// Homework Problem #3, top-down approach w/out MAX_LIVE
// old r5 => r1, old r2 => r1, old r4 => r2
// load base address into machine register
loadI 1024 => r0
// "old" r1 == r0, 0
loadI 1 => r4
storeAI r4 => r0, 0
// "old" r2 == r1
loadI 2 => r1
// "old" r3 == r0, 4
subI r1, 4 => r4
storeAI r4 => r0, 4
// "old" r4 == r2
loadAI r0, 0 => r4
add r4, r1 => r2
// "old" r5 == r1
addI r2, 1 => r1
// "old" r6 == r0, 8
loadAI r0, 4 => r4
mult r4, r1 => r4
storeAI r4 => r0, 8
// "old" r7 == r0, 12
loadAI r0, 8 => r5
sub r1, r5 => r4
storeAI r4 => r0, 12
// "old" r8 == r0, 16
add r2, r1 => r4
storeAI r4 => r0, 16
// "old" r9 == r0, 20
loadAI r0, 16 => r4
loadAI r0, 12 => r5
add r4, r5 => r4
storeAI r4 => r0, 20
// "old" r10 == r0, 24
loadAI r0, 20 => r4
loadAI r0, 0 => r5
add r4, r5 => r4
storeAI r4 => r0, 24
// output r10, or r0, 24
outputAI r0, 24