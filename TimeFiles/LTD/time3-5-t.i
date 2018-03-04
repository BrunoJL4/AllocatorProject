loadI 1024 => r0
loadI 1024 => r1
storeAI r1 => r0, -4
loadI 1028 => r1
storeAI r1 => r0, -8
loadI 4 => r5
loadAI r0, -4 => r1
load r1 => r2
storeAI r2 => r0, -20
loadAI r0, -8 => r1
load r1 => r2
storeAI r2 => r0, -12
loadI 2000 => r1
storeAI r1 => r0, -16
loadAI r0, -20 => r1
loadAI r0, -12 => r2
add r1, r2 => r4
loadAI r0, -20 => r1
add r4, r1 => r3
add r3, r4 => r1
storeAI r1 => r0, -24
loadAI r0, -24 => r1
add r1, r3 => r1
storeAI r1 => r0, -28
loadAI r0, -28 => r1
loadAI r0, -24 => r2
add r1, r2 => r1
storeAI r1 => r0, -32
loadAI r0, -32 => r1
loadAI r0, -28 => r2
add r1, r2 => r1
storeAI r1 => r0, -36
loadAI r0, -36 => r1
loadAI r0, -32 => r2
add r1, r2 => r1
storeAI r1 => r0, -40
loadAI r0, -40 => r1
loadAI r0, -36 => r2
add r1, r2 => r1
storeAI r1 => r0, -44
loadAI r0, -44 => r1
loadAI r0, -40 => r2
add r1, r2 => r1
storeAI r1 => r0, -48
loadAI r0, -48 => r1
loadAI r0, -44 => r2
add r1, r2 => r1
storeAI r1 => r0, -52
loadAI r0, -20 => r1
loadAI r0, -16 => r2
store r1 => r2
loadAI r0, -16 => r1
add r1, r5 => r1
storeAI r1 => r0, -56
loadAI r0, -56 => r2
store r4 => r2
loadAI r0, -56 => r1
add r1, r5 => r4
store r3 => r4
add r4, r5 => r3
loadAI r0, -24 => r1
store r1 => r3
add r3, r5 => r3
loadAI r0, -28 => r1
store r1 => r3
add r3, r5 => r3
loadAI r0, -32 => r1
store r1 => r3
add r3, r5 => r3
loadAI r0, -36 => r1
store r1 => r3
add r3, r5 => r3
loadAI r0, -40 => r1
store r1 => r3
add r3, r5 => r3
loadAI r0, -44 => r1
store r1 => r3
add r3, r5 => r3
loadAI r0, -48 => r1
store r1 => r3
add r3, r5 => r3
loadAI r0, -52 => r1
store r1 => r3
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
// Total time = 0.000861 seconds
