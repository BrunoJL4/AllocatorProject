loadI 1024 => r0
loadI 1024 => r1
loadI 1028 => r2
loadI 4 => r3
load r1 => r4
load r2 => r5
storeAI r1 => r0, -4
loadI 2000 => r1
storeAI r2 => r0, -8
add r4, r5 => r2
storeAI r5 => r0, -12
add r2, r4 => r5
storeAI r3 => r0, -16
add r5, r2 => r3
storeAI r2 => r0, -20
add r3, r5 => r2
storeAI r5 => r0, -24
add r2, r3 => r5
storeAI r3 => r0, -28
add r5, r2 => r3
storeAI r2 => r0, -32
add r3, r5 => r2
storeAI r5 => r0, -36
add r2, r3 => r5
storeAI r3 => r0, -40
add r5, r2 => r3
storeAI r2 => r0, -44
add r3, r5 => r2
store r4 => r1
storeAI r4 => r0, -48
storeAI r2 => r0, -52
loadAI r0, -16 => r2
add r1, r2 => r4
storeAI r1 => r0, -56
loadAI r0, -20 => r1
store r1 => r4
storeAI r1 => r0, -20
add r4, r2 => r1
storeAI r4 => r0, -60
loadAI r0, -24 => r4
store r4 => r1
storeAI r4 => r0, -24
add r1, r2 => r4
storeAI r1 => r0, -64
loadAI r0, -28 => r1
store r1 => r4
storeAI r1 => r0, -28
add r4, r2 => r1
storeAI r4 => r0, -68
loadAI r0, -32 => r4
store r4 => r1
storeAI r4 => r0, -32
add r1, r2 => r4
storeAI r1 => r0, -72
loadAI r0, -36 => r1
store r1 => r4
storeAI r1 => r0, -36
add r4, r2 => r1
storeAI r4 => r0, -76
loadAI r0, -40 => r4
store r4 => r1
storeAI r4 => r0, -40
add r1, r2 => r4
storeAI r1 => r0, -80
loadAI r0, -44 => r1
store r1 => r4
storeAI r1 => r0, -44
add r4, r2 => r1
store r5 => r1
storeAI r5 => r0, -84
add r1, r2 => r5
store r3 => r5
storeAI r3 => r0, -88
add r5, r2 => r3
storeAI r2 => r0, -16
loadAI r0, -52 => r2
store r2 => r3
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
// Total time = 0.001037 seconds
