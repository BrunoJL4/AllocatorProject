loadI 1024 => r0
loadI 4000 => r3
loadI 4 => r4
loadI 1 => r1
storeAI r1 => r0, -4
load r3 => r2
storeAI r2 => r0, -8
add r3, r4 => r1
storeAI r1 => r0, -12
loadAI r0, -12 => r1
load r1 => r2
storeAI r2 => r0, -24
loadAI r0, -12 => r1
add r1, r4 => r1
storeAI r1 => r0, -16
loadAI r0, -16 => r1
load r1 => r2
storeAI r2 => r0, -32
loadAI r0, -16 => r1
add r1, r4 => r1
storeAI r1 => r0, -20
loadAI r0, -20 => r1
load r1 => r2
storeAI r2 => r0, -40
loadAI r0, -20 => r1
add r1, r4 => r1
storeAI r1 => r0, -28
loadAI r0, -28 => r1
load r1 => r2
storeAI r2 => r0, -48
loadAI r0, -28 => r1
add r1, r4 => r1
storeAI r1 => r0, -36
loadAI r0, -36 => r1
load r1 => r5
loadAI r0, -36 => r1
add r1, r4 => r1
storeAI r1 => r0, -44
loadAI r0, -44 => r1
load r1 => r3
loadAI r0, -44 => r1
add r1, r4 => r1
storeAI r1 => r0, -52
loadAI r0, -52 => r1
load r1 => r2
storeAI r2 => r0, -56
loadAI r0, -52 => r1
add r1, r4 => r1
storeAI r1 => r0, -60
loadAI r0, -60 => r1
load r1 => r2
storeAI r2 => r0, -64
loadAI r0, -60 => r1
add r1, r4 => r1
storeAI r1 => r0, -68
loadAI r0, -68 => r1
load r1 => r2
storeAI r2 => r0, -72
loadAI r0, -68 => r1
add r1, r4 => r1
storeAI r1 => r0, -76
loadI 0 => r1
loadAI r0, -8 => r1
loadAI r0, -24 => r2
add r1, r2 => r1
storeAI r1 => r0, -80
loadAI r0, -4 => r1
loadAI r0, -24 => r2
mult r1, r2 => r1
storeAI r1 => r0, -84
loadAI r0, -72 => r1
loadAI r0, -8 => r2
sub r1, r2 => r1
storeAI r1 => r0, -88
loadAI r0, -80 => r1
loadAI r0, -32 => r2
add r1, r2 => r1
storeAI r1 => r0, -92
loadAI r0, -84 => r1
loadAI r0, -32 => r2
mult r1, r2 => r1
storeAI r1 => r0, -96
loadAI r0, -88 => r1
loadAI r0, -64 => r2
add r1, r2 => r1
storeAI r1 => r0, -100
loadAI r0, -92 => r1
loadAI r0, -40 => r2
add r1, r2 => r1
storeAI r1 => r0, -104
loadAI r0, -96 => r1
loadAI r0, -40 => r2
mult r1, r2 => r1
storeAI r1 => r0, -108
loadAI r0, -100 => r1
loadAI r0, -56 => r2
sub r1, r2 => r1
storeAI r1 => r0, -112
loadAI r0, -104 => r1
loadAI r0, -48 => r2
add r1, r2 => r1
storeAI r1 => r0, -116
loadAI r0, -108 => r1
loadAI r0, -48 => r2
mult r1, r2 => r1
storeAI r1 => r0, -120
loadAI r0, -112 => r1
add r1, r3 => r4
loadAI r0, -116 => r1
add r1, r5 => r1
storeAI r1 => r0, -124
loadAI r0, -120 => r1
mult r1, r5 => r1
storeAI r1 => r0, -128
sub r4, r5 => r1
storeAI r1 => r0, -132
loadAI r0, -124 => r1
add r1, r3 => r1
storeAI r1 => r0, -136
loadAI r0, -128 => r1
mult r1, r3 => r3
loadAI r0, -48 => r1
add r4, r1 => r1
storeAI r1 => r0, -140
loadI 16 => r5
rshift r3, r5 => r3
loadAI r0, -136 => r1
loadAI r0, -56 => r2
add r1, r2 => r1
storeAI r1 => r0, -144
loadAI r0, -56 => r1
mult r3, r1 => r1
storeAI r1 => r0, -148
loadAI r0, -140 => r1
loadAI r0, -40 => r2
sub r1, r2 => r1
storeAI r1 => r0, -152
loadAI r0, -144 => r1
loadAI r0, -64 => r2
add r1, r2 => r4
loadAI r0, -148 => r1
loadAI r0, -64 => r2
mult r1, r2 => r3
loadAI r0, -152 => r1
loadAI r0, -32 => r2
add r1, r2 => r5
loadAI r0, -72 => r1
add r4, r1 => r1
storeAI r1 => r0, -156
loadAI r0, -72 => r1
mult r3, r1 => r3
loadAI r0, -24 => r1
sub r5, r1 => r4
loadI 1024 => r5
loadAI r0, -156 => r1
store r1 => r5
loadI 1028 => r5
store r3 => r5
loadI 1032 => r3
store r4 => r3
output 1024
output 1028
output 1032
// Total time = 0.001632 seconds
