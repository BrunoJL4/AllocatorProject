#!/bin/sh
# Remove all test files that came before this.
echo "Removing previous test files"
rm test*
# Make the environment
make clean
make 
echo "Creating test files for simple top-down allocation"
# Create simple-TD test files- 5 registers
./alloc 5 s Test_Blocks/block1.i >> test1-5.i
./alloc 5 s Test_Blocks/block2.i >> test2-5.i
./alloc 5 s Test_Blocks/block3.i >> test3-5.i
./alloc 5 s Test_Blocks/block4.i >> test4-5.i
./alloc 5 s Test_Blocks/block5.i >> test5-5.i
./alloc 5 s Test_Blocks/block6.i >> test6-5.i
# Create simple-TD test files- 10 registers
./alloc 10 s Test_Blocks/block1.i >> test1-10.i
./alloc 10 s Test_Blocks/block2.i >> test2-10.i
./alloc 10 s Test_Blocks/block3.i >> test3-10.i
./alloc 10 s Test_Blocks/block4.i >> test4-10.i
./alloc 10 s Test_Blocks/block5.i >> test5-10.i
./alloc 10 s Test_Blocks/block6.i >> test6-10.i
# Create simple-TD test files- 20 registers
./alloc 20 s Test_Blocks/block1.i >> test1-20.i
./alloc 20 s Test_Blocks/block2.i >> test2-20.i
./alloc 20 s Test_Blocks/block3.i >> test3-20.i
./alloc 20 s Test_Blocks/block4.i >> test4-20.i
./alloc 20 s Test_Blocks/block5.i >> test5-20.i
./alloc 20 s Test_Blocks/block6.i >> test6-20.i

# Test each of these in waves: original block, 5-reg, 10-reg, and 20-reg.
echo "Performing test 1!"
./ILOC_Simulator/sim -i 1024 1 1 < Test_Blocks/block1.i
./ILOC_Simulator/sim -i 1024 1 1 < test1-5.i
./ILOC_Simulator/sim -i 1024 1 1 < test1-10.i
./ILOC_Simulator/sim -i 1024 1 1 < test1-20.i
echo "Test 1 finished!"

echo "Performing test 2!"
./ILOC_Simulator/sim < Test_Blocks/block2.i
./ILOC_Simulator/sim < test2-5.i
./ILOC_Simulator/sim < test2-10.i
./ILOC_Simulator/sim < test2-20.i
echo "Test 2 finished!"

echo "Performing test 3!"
./ILOC_Simulator/sim -i 1024 1 1 < Test_Blocks/block3.i
./ILOC_Simulator/sim -i 1024 1 1 < test3-5.i
./ILOC_Simulator/sim -i 1024 1 1 < test3-10.i
./ILOC_Simulator/sim -i 1024 1 1 < test3-20.i
echo "Test 3 finished!"

echo "Performing test 4!"
./ILOC_Simulator/sim -i 1024 1 1 < Test_Blocks/block4.i
./ILOC_Simulator/sim -i 1024 1 1 < test4-5.i
./ILOC_Simulator/sim -i 1024 1 1 < test4-10.i
./ILOC_Simulator/sim -i 1024 1 1 < test4-20.i
echo "Test 4 finished!"

echo "Performing test 5!"
./ILOC_Simulator/sim -i 1024 3 5 < Test_Blocks/block5.i
./ILOC_Simulator/sim -i 1024 3 5 < test5-5.i
./ILOC_Simulator/sim -i 1024 3 5 < test5-10.i
./ILOC_Simulator/sim -i 1024 3 5 < test5-20.i
echo "Test 5 finished!"

echo "Performing test 6!"
./ILOC_Simulator/sim -i 1024 3 5 < Test_Blocks/block6.i
./ILOC_Simulator/sim -i 1024 3 5 < test6-5.i
./ILOC_Simulator/sim -i 1024 3 5 < test6-10.i
./ILOC_Simulator/sim -i 1024 3 5 < test6-20.i
echo "Test 6 finished!"

# Clean everything up
echo "Cleaning up environment!"
make clean
rm test*
