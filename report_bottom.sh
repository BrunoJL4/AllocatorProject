#!/bin/sh
# Remove all test files that came before this.
echo "Removing previous report files"
rm test*
# Make the environment
make clean
make 
echo "Creating report files for simple top-down allocation"
# Create simple-TD report files- 5 registers
./alloc 5 b Report_Blocks/report1.i >> test1-5.i
./alloc 5 b Report_Blocks/report2.i >> test2-5.i
./alloc 5 b Report_Blocks/report3.i >> test3-5.i
./alloc 5 b Report_Blocks/report4.i >> test4-5.i
./alloc 5 b Report_Blocks/report5.i >> test5-5.i
./alloc 5 b Report_Blocks/report6.i >> test6-5.i
# Create simple-TD report files- 10 registers
./alloc 10 b Report_Blocks/report1.i >> test1-10.i
./alloc 10 b Report_Blocks/report2.i >> test2-10.i
./alloc 10 b Report_Blocks/report3.i >> test3-10.i
./alloc 10 b Report_Blocks/report4.i >> test4-10.i
./alloc 10 b Report_Blocks/report5.i >> test5-10.i
./alloc 10 b Report_Blocks/report6.i >> test6-10.i
# Create simple-TD report files- 20 registers
./alloc 20 b Report_Blocks/report1.i >> test1-20.i
./alloc 20 b Report_Blocks/report2.i >> test2-20.i
./alloc 20 b Report_Blocks/report3.i >> test3-20.i
./alloc 20 b Report_Blocks/report4.i >> test4-20.i
./alloc 20 b Report_Blocks/report5.i >> test5-20.i
./alloc 20 b Report_Blocks/report6.i >> test6-20.i

# Test each of these in waves: original block, 5-reg, 10-reg, and 20-reg.
echo "Performing test 1!"
./ILOC_Simulator/sim -i 4000 0 10 20 30 40 50 60 70 80 90 < report1.i
./ILOC_Simulator/sim -i 4000 0 10 20 30 40 50 60 70 80 90 < test1-5.i
./ILOC_Simulator/sim -i 4000 0 10 20 30 40 50 60 70 80 90 < test1-10.i
./ILOC_Simulator/sim -i 4000 0 10 20 30 40 50 60 70 80 90 < test1-20.i
echo "Test 1 finished!"

echo "Performing test 2!"
./ILOC_Simulator/sim -i 1024 0 1 < Report_Blocks/report2.i
./ILOC_Simulator/sim -i 1024 0 1 < test2-5.i
./ILOC_Simulator/sim -i 1024 0 1 < test2-10.i
./ILOC_Simulator/sim -i 1024 0 1 < test2-20.i
echo "Test 2 finished!"

echo "Performing test 3!"
./ILOC_Simulator/sim -i 1024 0 1 < Report_Blocks/report3.i
./ILOC_Simulator/sim -i 1024 0 1 < test3-5.i
./ILOC_Simulator/sim -i 1024 0 1 < test3-10.i
./ILOC_Simulator/sim -i 1024 0 1 < test3-20.i
echo "Test 3 finished!"

echo "Performing test 4!"
./ILOC_Simulator/sim -i 1024 0 1 2 < Report_Blocks/report4.i
./ILOC_Simulator/sim -i 1024 0 1 2 < test4-5.i
./ILOC_Simulator/sim -i 1024 0 1 2 < test4-10.i
./ILOC_Simulator/sim -i 1024 0 1 2 < test4-20.i
echo "Test 4 finished!"

echo "Performing test 5!"
./ILOC_Simulator/sim -i 1024 1 < Report_Blocks/report5.i
./ILOC_Simulator/sim -i 1024 1 < test5-5.i
./ILOC_Simulator/sim -i 1024 1 < test5-10.i
./ILOC_Simulator/sim -i 1024 1 < test5-20.i
echo "Test 5 finished!"

echo "Performing test 6!"
./ILOC_Simulator/sim -i 1024 0 1 < Report_Blocks/report6.i
./ILOC_Simulator/sim -i 1024 0 1 < test6-5.i
./ILOC_Simulator/sim -i 1024 0 1 < test6-10.i
./ILOC_Simulator/sim -i 1024 0 1 < test6-20.i
echo "Test 6 finished!"

# Clean everything up
echo "Cleaning up environment!"
make clean
rm test*
