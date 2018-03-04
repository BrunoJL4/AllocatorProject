loadI 1024 => r0
loadI 1024 => r1
storeAI r1 => r0, -16
loadI 1028 => r1
storeAI r1 => r0, -20
loadI 4 => r3
loadAI r0, -16 => r1
load r1 => r4
loadAI r0, -20 => r1
load r1 => r2
storeAI r2 => r0, -24
loadI 2000 => r13
loadAI r0, -24 => r1
add r4, r1 => r5
add r5, r4 => r6
add r6, r5 => r7
add r7, r6 => r8
add r8, r7 => r9
add r9, r8 => r10
add r10, r9 => r11
add r11, r10 => r12
add r12, r11 => r14
add r14, r12 => r1
storeAI r1 => r0, -28
store r4 => r13
add r13, r3 => r15
store r5 => r15
add r15, r3 => r16
store r6 => r16
add r16, r3 => r17
store r7 => r17
add r17, r3 => r18
store r8 => r18
add r18, r3 => r19
store r9 => r19
add r19, r3 => r20
store r10 => r20
add r20, r3 => r1
storeAI r1 => r0, -4
loadAI r0, -4 => r2
store r11 => r2
loadAI r0, -4 => r1
add r1, r3 => r1
storeAI r1 => r0, -8
loadAI r0, -8 => r2
store r12 => r2
loadAI r0, -8 => r1
add r1, r3 => r1
storeAI r1 => r0, -12
loadAI r0, -12 => r2
store r14 => r2
loadAI r0, -12 => r1
add r1, r3 => r1
storeAI r1 => r0, -32
loadAI r0, -28 => r1
loadAI r0, -32 => r2
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
// Total time = 0.000586 seconds
