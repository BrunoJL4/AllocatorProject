loadI 1024 => r0
loadI 1024 => r3
load r3 => r3
loadI 4 => r1
storeAI r1 => r0, -4
loadI 1024 => r1
storeAI r1 => r0, -8
lshift r3, r3 => r1
storeAI r1 => r0, -12
loadAI r0, -12 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -16
loadAI r0, -16 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -20
loadAI r0, -20 => r1
lshift r1, r3 => r5
lshift r5, r3 => r1
storeAI r1 => r0, -24
loadAI r0, -24 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -28
loadAI r0, -28 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -32
loadAI r0, -32 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -36
loadAI r0, -36 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -40
loadAI r0, -40 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -44
loadAI r0, -44 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -48
loadAI r0, -48 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -52
loadAI r0, -52 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -56
loadAI r0, -56 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -60
loadAI r0, -60 => r1
lshift r1, r3 => r4
lshift r4, r3 => r1
storeAI r1 => r0, -64
loadAI r0, -12 => r1
add r3, r1 => r1
storeAI r1 => r0, -68
loadAI r0, -16 => r1
loadAI r0, -20 => r2
add r1, r2 => r1
storeAI r1 => r0, -72
loadAI r0, -24 => r1
add r5, r1 => r1
storeAI r1 => r0, -76
loadAI r0, -28 => r1
loadAI r0, -32 => r2
add r1, r2 => r1
storeAI r1 => r0, -80
loadAI r0, -36 => r1
loadAI r0, -40 => r2
add r1, r2 => r1
storeAI r1 => r0, -84
loadAI r0, -44 => r1
loadAI r0, -48 => r2
add r1, r2 => r1
storeAI r1 => r0, -88
loadAI r0, -52 => r1
loadAI r0, -56 => r2
add r1, r2 => r1
storeAI r1 => r0, -92
loadAI r0, -60 => r1
add r1, r4 => r1
storeAI r1 => r0, -96
loadAI r0, -68 => r1
loadAI r0, -72 => r2
add r1, r2 => r1
storeAI r1 => r0, -100
loadAI r0, -76 => r1
loadAI r0, -80 => r2
add r1, r2 => r1
storeAI r1 => r0, -104
loadAI r0, -84 => r1
loadAI r0, -88 => r2
add r1, r2 => r1
storeAI r1 => r0, -108
loadAI r0, -92 => r1
loadAI r0, -96 => r2
add r1, r2 => r1
storeAI r1 => r0, -112
loadAI r0, -100 => r1
loadAI r0, -104 => r2
add r1, r2 => r1
storeAI r1 => r0, -116
loadAI r0, -108 => r1
loadAI r0, -112 => r2
add r1, r2 => r1
storeAI r1 => r0, -120
loadAI r0, -120 => r1
loadAI r0, -116 => r2
add r1, r2 => r1
storeAI r1 => r0, -124
loadAI r0, -124 => r1
loadAI r0, -64 => r2
add r1, r2 => r4
loadAI r0, -8 => r2
store r4 => r2
add r5, r3 => r4
lshift r3, r4 => r4
sub r4, r3 => r3
loadAI r0, -8 => r1
loadAI r0, -4 => r2
add r1, r2 => r4
store r3 => r4
output 1024
output 1028
// Total time = 0.001106 seconds