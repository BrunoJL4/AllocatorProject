loadI 1024 => r0
loadI 1024 => r3
loadI 1028 => r4
loadI 4 => r5
load r3 => r3
load r4 => r4
loadI 2000 => r6
add r3, r4 => r4
add r4, r3 => r7
add r7, r4 => r8
add r8, r7 => r9
add r9, r8 => r10
add r10, r9 => r11
add r11, r10 => r12
add r12, r11 => r13
add r13, r12 => r14
add r14, r13 => r15
store r3 => r6
add r6, r5 => r3
store r4 => r3
add r3, r5 => r3
store r7 => r3
add r3, r5 => r3
store r8 => r3
add r3, r5 => r3
store r9 => r3
add r3, r5 => r3
store r10 => r3
add r3, r5 => r3
store r11 => r3
add r3, r5 => r3
store r12 => r3
add r3, r5 => r3
store r13 => r3
add r3, r5 => r3
store r14 => r3
add r3, r5 => r3
store r15 => r3
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
// Total time = 0.000785 seconds
