loadI 1024 => r0
loadI 4000 => r3
loadI 4 => r4
loadI 1 => r1
storeAI r1 => r0, -4
load r3 => r2
storeAI r2 => r0, -8
add r3, r4 => r3
load r3 => r2
storeAI r2 => r0, -24
add r3, r4 => r3
load r3 => r2
storeAI r2 => r0, -32
add r3, r4 => r3
load r3 => r9
add r3, r4 => r3
load r3 => r10
add r3, r4 => r3
load r3 => r5
add r3, r4 => r1
storeAI r1 => r0, -12
loadAI r0, -12 => r1
load r1 => r6
loadAI r0, -12 => r1
add r1, r4 => r1
storeAI r1 => r0, -16
loadAI r0, -16 => r1
load r1 => r3
loadAI r0, -16 => r1
add r1, r4 => r1
storeAI r1 => r0, -20
loadAI r0, -20 => r1
load r1 => r7
loadAI r0, -20 => r1
add r1, r4 => r1
storeAI r1 => r0, -28
loadAI r0, -28 => r1
load r1 => r8
loadAI r0, -28 => r1
add r1, r4 => r1
storeAI r1 => r0, -36
loadI 0 => r1
loadAI r0, -8 => r1
loadAI r0, -24 => r2
add r1, r2 => r1
storeAI r1 => r0, -40
loadAI r0, -4 => r1
loadAI r0, -24 => r2
mult r1, r2 => r1
storeAI r1 => r0, -44
loadAI r0, -8 => r1
sub r8, r1 => r1
storeAI r1 => r0, -48
loadAI r0, -40 => r1
loadAI r0, -32 => r2
add r1, r2 => r1
storeAI r1 => r0, -52
loadAI r0, -44 => r1
loadAI r0, -32 => r2
mult r1, r2 => r1
storeAI r1 => r0, -56
loadAI r0, -48 => r1
add r1, r7 => r1
storeAI r1 => r0, -60
loadAI r0, -52 => r1
add r1, r9 => r1
storeAI r1 => r0, -64
loadAI r0, -56 => r1
mult r1, r9 => r1
storeAI r1 => r0, -68
loadAI r0, -60 => r1
sub r1, r3 => r1
storeAI r1 => r0, -72
loadAI r0, -64 => r1
add r1, r10 => r1
storeAI r1 => r0, -76
loadAI r0, -68 => r1
mult r1, r10 => r1
storeAI r1 => r0, -80
loadAI r0, -72 => r1
add r1, r6 => r4
loadAI r0, -76 => r1
add r1, r5 => r1
storeAI r1 => r0, -84
loadAI r0, -80 => r1
mult r1, r5 => r1
storeAI r1 => r0, -88
sub r4, r5 => r1
storeAI r1 => r0, -92
loadAI r0, -84 => r1
add r1, r6 => r1
storeAI r1 => r0, -96
loadAI r0, -88 => r1
mult r1, r6 => r5
add r4, r10 => r4
loadI 16 => r6
rshift r5, r6 => r5
loadAI r0, -96 => r1
add r1, r3 => r6
mult r5, r3 => r3
sub r4, r9 => r4
add r6, r7 => r5
mult r3, r7 => r3
loadAI r0, -32 => r1
add r4, r1 => r4
add r5, r8 => r5
mult r3, r8 => r3
loadAI r0, -24 => r1
sub r4, r1 => r4
loadI 1024 => r6
store r5 => r6
loadI 1028 => r5
store r3 => r5
loadI 1032 => r3
store r4 => r3
output 1024
output 1028
output 1032
// Total time = 0.001527 seconds