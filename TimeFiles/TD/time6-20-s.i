loadI 1024 => r0
loadI 1028 => r20
load r0 => r2
storeAI r2 => r0, -4
load r20 => r3
loadI 4 => r1
storeAI r1 => r0, -8
loadI 1024 => r4
loadAI r0, -4 => r1
add r1, r3 => r1
storeAI r1 => r0, -12
lshift r3, r3 => r5
loadAI r0, -12 => r1
add r1, r5 => r1
storeAI r1 => r0, -16
lshift r5, r3 => r6
loadAI r0, -16 => r1
add r1, r6 => r1
storeAI r1 => r0, -20
lshift r6, r3 => r7
loadAI r0, -20 => r1
add r1, r7 => r1
storeAI r1 => r0, -24
lshift r7, r3 => r8
loadAI r0, -24 => r1
add r1, r8 => r1
storeAI r1 => r0, -28
lshift r8, r3 => r9
loadAI r0, -28 => r1
add r1, r9 => r1
storeAI r1 => r0, -32
lshift r9, r3 => r10
loadAI r0, -32 => r1
add r1, r10 => r1
storeAI r1 => r0, -36
lshift r10, r3 => r11
loadAI r0, -36 => r1
add r1, r11 => r1
storeAI r1 => r0, -40
lshift r11, r3 => r12
loadAI r0, -40 => r1
add r1, r12 => r1
storeAI r1 => r0, -44
lshift r12, r3 => r13
loadAI r0, -44 => r1
add r1, r13 => r1
storeAI r1 => r0, -48
lshift r13, r3 => r14
loadAI r0, -48 => r1
add r1, r14 => r1
storeAI r1 => r0, -52
lshift r14, r3 => r15
loadAI r0, -52 => r1
add r1, r15 => r1
storeAI r1 => r0, -56
lshift r15, r3 => r16
loadAI r0, -56 => r1
add r1, r16 => r1
storeAI r1 => r0, -60
lshift r16, r3 => r17
loadAI r0, -60 => r1
add r1, r17 => r1
storeAI r1 => r0, -64
lshift r17, r3 => r18
loadAI r0, -64 => r1
add r1, r18 => r1
storeAI r1 => r0, -68
lshift r18, r3 => r19
loadAI r0, -68 => r1
add r1, r19 => r1
storeAI r1 => r0, -72
lshift r19, r3 => r1
storeAI r1 => r0, -76
loadAI r0, -72 => r1
loadAI r0, -76 => r2
add r1, r2 => r1
storeAI r1 => r0, -80
loadAI r0, -80 => r1
store r1 => r4
loadI 17 => r1
storeAI r1 => r0, -84
loadAI r0, -84 => r1
lshift r3, r1 => r1
storeAI r1 => r0, -88
loadAI r0, -88 => r1
sub r1, r3 => r1
storeAI r1 => r0, -92
loadAI r0, -8 => r1
add r4, r1 => r1
storeAI r1 => r0, -96
loadAI r0, -92 => r1
loadAI r0, -96 => r2
store r1 => r2
output 1024
output 1028
// Total time = 0.000752 seconds
