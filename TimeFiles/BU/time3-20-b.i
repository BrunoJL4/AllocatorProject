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
add r10, r9 => r11
add r11, r10 => r12
add r12, r11 => r13
add r13, r12 => r14
add r14, r13 => r15
add r15, r14 => r16
store r4 => r6
add r6, r3 => r17
store r7 => r17
add r17, r3 => r18
store r8 => r18
add r18, r3 => r19
store r9 => r19
add r19, r3 => r20
store r10 => r20
storeAI r1 => r0, -4
add r20, r3 => r1
store r11 => r1
storeAI r2 => r0, -8
add r1, r3 => r2
store r12 => r2
storeAI r4 => r0, -12
add r2, r3 => r4
store r13 => r4
storeAI r5 => r0, -16
add r4, r3 => r5
store r14 => r5
storeAI r6 => r0, -20
add r5, r3 => r6
store r15 => r6
storeAI r7 => r0, -24
add r6, r3 => r7
store r16 => r7
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
// Total time = 0.001394 seconds
