// Homework 1 problem #1, register-register model
// result should be: 20 with given inputs
// Assign STATIC_AREA_ADDRESS to r0 by default;
loadI 1024 => r0 // test blahblah
// a == 1;  r1 == a
loadI 1 => r1
// b == 2;  r2 == b
loadI 2 => r2 // test moreblahblah
// c == b - 4;  r3 == c
subI r2, 4 => r3
// d == a + b;  r4 == d
add r1, r2 => r4
// e == d + 1;  r5 == e
addI r4, 1 => r5
// f == e - c * e... r6 == c * e;  r7 == r5 - r6 == f;
mult r3, r5 => r6
sub r5, r6 => r7
// g == (d + e) + f... r8 == d + e;  r9 == r8 + r7 == g
add r4, r5 => r8
add r8, r7 => r9
// h == g + a; r10 == r9 + r1 == h
add r9, r1 => r10
// store r10 into memory at r0, 0... then output
storeAI r10 => r0, 0
outputAI r0, 0


