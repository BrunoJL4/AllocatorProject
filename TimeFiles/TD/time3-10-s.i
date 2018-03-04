loadI 1024 => r0
loadI 1024 => r1
storeAI r1 => r0, -56
loadI 1028 => r1
storeAI r1 => r0, -60
loadI 4 => r3
loadAI r0, -56 => r1
load r1 => r4
loadAI r0, -60 => r1
load r1 => r2
storeAI r2 => r0, -64
loadI 2000 => r1
storeAI r1 => r0, -12
loadAI r0, -64 => r1
add r4, r1 => r5
add r5, r4 => r6
add r6, r5 => r7
add r7, r6 => r8
add r8, r7 => r9
add r9, r8 => r10
add r10, r9 => r1
storeAI r1 => r0, -4
loadAI r0, -4 => r1
add r1, r10 => r1
storeAI r1 => r0, -8
loadAI r0, -8 => r1
loadAI r0, -4 => r2
add r1, r2 => r1
storeAI r1 => r0, -16
loadAI r0, -16 => r1
loadAI r0, -8 => r2
add r1, r2 => r1
storeAI r1 => r0, -68
loadAI r0, -12 => r2
store r4 => r2
loadAI r0, -12 => r1
add r1, r3 => r1
storeAI r1 => r0, -20
loadAI r0, -20 => r2
store r5 => r2
loadAI r0, -20 => r1
add r1, r3 => r1
storeAI r1 => r0, -24
loadAI r0, -24 => r2
store r6 => r2
loadAI r0, -24 => r1
add r1, r3 => r1
storeAI r1 => r0, -28
loadAI r0, -28 => r2
store r7 => r2
loadAI r0, -28 => r1
add r1, r3 => r1
storeAI r1 => r0, -32
loadAI r0, -32 => r2
store r8 => r2
loadAI r0, -32 => r1
add r1, r3 => r1
storeAI r1 => r0, -36
loadAI r0, -36 => r2
store r9 => r2
loadAI r0, -36 => r1
add r1, r3 => r1
storeAI r1 => r0, -40
loadAI r0, -40 => r2
store r10 => r2
loadAI r0, -40 => r1
add r1, r3 => r1
storeAI r1 => r0, -44
loadAI r0, -4 => r1
loadAI r0, -44 => r2
store r1 => r2
loadAI r0, -44 => r1
add r1, r3 => r1
storeAI r1 => r0, -48
loadAI r0, -8 => r1
loadAI r0, -48 => r2
store r1 => r2
loadAI r0, -48 => r1
add r1, r3 => r1
storeAI r1 => r0, -52
loadAI r0, -16 => r1
loadAI r0, -52 => r2
store r1 => r2
loadAI r0, -52 => r1
add r1, r3 => r1
storeAI r1 => r0, -72
loadAI r0, -68 => r1
loadAI r0, -72 => r2
store r1 => r2
output 2000
output 2004
output 2008
output 2012
output 2016
output 2020
output 2024
output 2028
output 2032
output 2036
output 2040
// Total time = 0.000508 seconds
