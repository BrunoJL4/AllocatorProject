loadI 1024 => r0
loadI 1024 => r3
load r3 => r3
loadI 4 => r1
storeAI r1 => r0, -4
loadI 1024 => r5
lshift r3, r3 => r6
lshift r6, r3 => r7
lshift r7, r3 => r8
lshift r8, r3 => r9
lshift r9, r3 => r10
lshift r10, r3 => r11
lshift r11, r3 => r12
lshift r12, r3 => r13
lshift r13, r3 => r14
lshift r14, r3 => r15
lshift r15, r3 => r16
lshift r16, r3 => r17
lshift r17, r3 => r18
lshift r18, r3 => r19
lshift r19, r3 => r20
lshift r20, r3 => r1
storeAI r1 => r0, -8
add r3, r6 => r4
add r7, r8 => r6
add r9, r10 => r7
add r11, r12 => r8
add r13, r14 => r10
add r15, r16 => r11
add r17, r18 => r12
add r19, r20 => r13
add r4, r6 => r4
add r7, r8 => r6
add r10, r11 => r7
add r12, r13 => r8
add r4, r6 => r4
add r7, r8 => r6
add r6, r4 => r4
loadAI r0, -8 => r1
add r4, r1 => r4
store r4 => r5
add r9, r3 => r4
lshift r3, r4 => r4
sub r4, r3 => r3
loadAI r0, -4 => r1
add r5, r1 => r4
store r3 => r4
output 1024
output 1028
// Total time = 0.000900 seconds