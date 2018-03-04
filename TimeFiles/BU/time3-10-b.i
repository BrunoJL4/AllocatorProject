loadI 1024 => r0
loadI 1024 => r1
loadI 1028 => r2
loadI 4 => r3
load r1 => r4
load r2 => r5
loadI 2000 => r6
add r4, r5 => r7
add r7, r4 => r8
add r8, r7 => r9
add r9, r8 => r10
storeAI r1 => r0, -4
add r10, r9 => r1
storeAI r2 => r0, -8
add r1, r10 => r2
storeAI r5 => r0, -12
add r2, r1 => r5
storeAI r1 => r0, -16
add r5, r2 => r1
storeAI r2 => r0, -20
add r1, r5 => r2
storeAI r5 => r0, -24
add r2, r1 => r5
store r4 => r6
storeAI r4 => r0, -28
add r6, r3 => r4
store r7 => r4
storeAI r6 => r0, -32
add r4, r3 => r6
store r8 => r6
storeAI r7 => r0, -36
add r6, r3 => r7
store r9 => r7
storeAI r8 => r0, -40
add r7, r3 => r8
store r10 => r8
storeAI r9 => r0, -44
add r8, r3 => r9
storeAI r10 => r0, -48
loadAI r0, -16 => r10
store r10 => r9
storeAI r10 => r0, -16
add r9, r3 => r10
storeAI r4 => r0, -52
loadAI r0, -20 => r4
store r4 => r10
storeAI r4 => r0, -20
add r10, r3 => r4
storeAI r6 => r0, -56
loadAI r0, -24 => r6
store r6 => r4
storeAI r6 => r0, -24
add r4, r3 => r6
store r1 => r6
storeAI r1 => r0, -60
add r6, r3 => r1
store r2 => r1
storeAI r2 => r0, -64
add r1, r3 => r2
store r5 => r2
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
// Total time = 0.001196 seconds
