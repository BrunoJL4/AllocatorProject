loadI 1024 => r0
loadI 1024 => r1
storeAI r1 => r0, -60
loadAI r0, -60 => r1
load r1 => r3
loadI 4 => r1
storeAI r1 => r0, -64
loadI 1024 => r5
lshift r3, r3 => r1
storeAI r1 => r0, -4
loadAI r0, -4 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -8
loadAI r0, -8 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -12
loadAI r0, -12 => r1
lshift r1, r3 => r4
lshift r4, r3 => r1
storeAI r1 => r0, -16
loadAI r0, -16 => r1
lshift r1, r3 => r1
storeAI r1 => r0, -20
loadAI r0, -20 => r1
lshift r1, r3 => r1
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
storeAI r1 => r0, -68
loadAI r0, -4 => r1
add r3, r1 => r1
storeAI r1 => r0, -72
loadAI r0, -8 => r1
loadAI r0, -12 => r2
add r1, r2 => r1
storeAI r1 => r0, -76
loadAI r0, -16 => r1
add r4, r1 => r1
storeAI r1 => r0, -80
loadAI r0, -20 => r1
loadAI r0, -24 => r2
add r1, r2 => r1
storeAI r1 => r0, -84
loadAI r0, -28 => r1
loadAI r0, -32 => r2
add r1, r2 => r1
storeAI r1 => r0, -88
loadAI r0, -36 => r1
loadAI r0, -40 => r2
add r1, r2 => r1
storeAI r1 => r0, -92
loadAI r0, -44 => r1
loadAI r0, -48 => r2
add r1, r2 => r1
storeAI r1 => r0, -96
loadAI r0, -52 => r1
loadAI r0, -56 => r2
add r1, r2 => r1
storeAI r1 => r0, -100
loadAI r0, -72 => r1
loadAI r0, -76 => r2
add r1, r2 => r1
storeAI r1 => r0, -104
loadAI r0, -80 => r1
loadAI r0, -84 => r2
add r1, r2 => r1
storeAI r1 => r0, -108
loadAI r0, -88 => r1
loadAI r0, -92 => r2
add r1, r2 => r1
storeAI r1 => r0, -112
loadAI r0, -96 => r1
loadAI r0, -100 => r2
add r1, r2 => r1
storeAI r1 => r0, -116
loadAI r0, -104 => r1
loadAI r0, -108 => r2
add r1, r2 => r1
storeAI r1 => r0, -120
loadAI r0, -112 => r1
loadAI r0, -116 => r2
add r1, r2 => r1
storeAI r1 => r0, -124
loadAI r0, -124 => r1
loadAI r0, -120 => r2
add r1, r2 => r1
storeAI r1 => r0, -128
loadAI r0, -128 => r1
loadAI r0, -68 => r2
add r1, r2 => r1
storeAI r1 => r0, -132
loadAI r0, -132 => r1
store r1 => r5
add r4, r3 => r1
storeAI r1 => r0, -136
loadAI r0, -136 => r1
lshift r3, r1 => r1
storeAI r1 => r0, -140
loadAI r0, -140 => r1
sub r1, r3 => r1
storeAI r1 => r0, -144
loadAI r0, -64 => r1
add r5, r1 => r1
storeAI r1 => r0, -148
loadAI r0, -144 => r1
loadAI r0, -148 => r2
store r1 => r2
output 1024
output 1028
// Total time = 0.000849 seconds
