#!/bin/sh
# Remove all test files that came before this.
echo "Removing previous report files"
rm -r TimeFiles
echo "Creating TimeFiles directory"
mkdir TimeFiles
echo "Creating TimeFiles sub-directories"
mkdir TimeFiles/TD
mkdir TimeFiles/LTD
mkdir TimeFiles/BU
# Make the environment
make clean
make 
echo "Creating report files for simple top-down allocation"
# Create simple-TD report files- 5 registers
./alloc 5 s Report_Blocks/report1.i >> TimeFiles/TD/time1-5-s.i
./alloc 5 s Report_Blocks/report2.i >> TimeFiles/TD/time2-5-s.i
./alloc 5 s Report_Blocks/report3.i >> TimeFiles/TD/time3-5-s.i
./alloc 5 s Report_Blocks/report4.i >> TimeFiles/TD/time4-5-s.i
./alloc 5 s Report_Blocks/report5.i >> TimeFiles/TD/time5-5-s.i
./alloc 5 s Report_Blocks/report6.i >> TimeFiles/TD/time6-5-s.i
# Create simple-TD report files- 10 registers
./alloc 10 s Report_Blocks/report1.i >> TimeFiles/TD/time1-10-s.i
./alloc 10 s Report_Blocks/report2.i >> TimeFiles/TD/time2-10-s.i
./alloc 10 s Report_Blocks/report3.i >> TimeFiles/TD/time3-10-s.i
./alloc 10 s Report_Blocks/report4.i >> TimeFiles/TD/time4-10-s.i
./alloc 10 s Report_Blocks/report5.i >> TimeFiles/TD/time5-10-s.i
./alloc 10 s Report_Blocks/report6.i >> TimeFiles/TD/time6-10-s.i
# Create simple-TD report files- 20 registers
./alloc 20 s Report_Blocks/report1.i >> TimeFiles/TD/time1-20-s.i
./alloc 20 s Report_Blocks/report2.i >> TimeFiles/TD/time2-20-s.i
./alloc 20 s Report_Blocks/report3.i >> TimeFiles/TD/time3-20-s.i
./alloc 20 s Report_Blocks/report4.i >> TimeFiles/TD/time4-20-s.i
./alloc 20 s Report_Blocks/report5.i >> TimeFiles/TD/time5-20-s.i
./alloc 20 s Report_Blocks/report6.i >> TimeFiles/TD/time6-20-s.i
echo
echo
echo "Creating report files for LECTURE top-down allocation"
# Create lecture-TD report files- 5 registers
./alloc 5 t Report_Blocks/report1.i >> TimeFiles/LTD/time1-5-t.i
./alloc 5 t Report_Blocks/report2.i >> TimeFiles/LTD/time2-5-t.i
./alloc 5 t Report_Blocks/report3.i >> TimeFiles/LTD/time3-5-t.i
./alloc 5 t Report_Blocks/report4.i >> TimeFiles/LTD/time4-5-t.i
./alloc 5 t Report_Blocks/report5.i >> TimeFiles/LTD/time5-5-t.i
./alloc 5 t Report_Blocks/report6.i >> TimeFiles/LTD/time6-5-t.i
# Create lecture-TD report files- 10 registers
./alloc 10 t Report_Blocks/report1.i >> TimeFiles/LTD/time1-10-t.i
./alloc 10 t Report_Blocks/report2.i >> TimeFiles/LTD/time2-10-t.i
./alloc 10 t Report_Blocks/report3.i >> TimeFiles/LTD/time3-10-t.i
./alloc 10 t Report_Blocks/report4.i >> TimeFiles/LTD/time4-10-t.i
./alloc 10 t Report_Blocks/report5.i >> TimeFiles/LTD/time5-10-t.i
./alloc 10 t Report_Blocks/report6.i >> TimeFiles/LTD/time6-10-t.i
# Create lecture-TD report files- 20 registers
./alloc 20 t Report_Blocks/report1.i >> TimeFiles/LTD/time1-20-t.i
./alloc 20 t Report_Blocks/report2.i >> TimeFiles/LTD/time2-20-t.i
./alloc 20 t Report_Blocks/report3.i >> TimeFiles/LTD/time3-20-t.i
./alloc 20 t Report_Blocks/report4.i >> TimeFiles/LTD/time4-20-t.i
./alloc 20 t Report_Blocks/report5.i >> TimeFiles/LTD/time5-20-t.i
./alloc 20 t Report_Blocks/report6.i >> TimeFiles/LTD/time6-20-t.i
echo
echo
echo "Creating report files for bottom-up allocation"
# Create bottom-up report files- 5 registers
./alloc 5 b Report_Blocks/report1.i >> TimeFiles/BU/time1-5-b.i
./alloc 5 b Report_Blocks/report2.i >> TimeFiles/BU/time2-5-b.i
./alloc 5 b Report_Blocks/report3.i >> TimeFiles/BU/time3-5-b.i
./alloc 5 b Report_Blocks/report4.i >> TimeFiles/BU/time4-5-b.i
./alloc 5 b Report_Blocks/report5.i >> TimeFiles/BU/time5-5-b.i
./alloc 5 b Report_Blocks/report6.i >> TimeFiles/BU/time6-5-b.i
# Create bottom-up report files- 10 registers
./alloc 10 b Report_Blocks/report1.i >> TimeFiles/BU/time1-10-b.i
./alloc 10 b Report_Blocks/report2.i >> TimeFiles/BU/time2-10-b.i
./alloc 10 b Report_Blocks/report3.i >> TimeFiles/BU/time3-10-b.i
./alloc 10 b Report_Blocks/report4.i >> TimeFiles/BU/time4-10-b.i
./alloc 10 b Report_Blocks/report5.i >> TimeFiles/BU/time5-10-b.i
./alloc 10 b Report_Blocks/report6.i >> TimeFiles/BU/time6-10-b.i
# Create bottom-up report files- 20 registers
./alloc 20 b Report_Blocks/report1.i >> TimeFiles/BU/time1-20-b.i
./alloc 20 b Report_Blocks/report2.i >> TimeFiles/BU/time2-20-b.i
./alloc 20 b Report_Blocks/report3.i >> TimeFiles/BU/time3-20-b.i
./alloc 20 b Report_Blocks/report4.i >> TimeFiles/BU/time4-20-b.i
./alloc 20 b Report_Blocks/report5.i >> TimeFiles/BU/time5-20-b.i
./alloc 20 b Report_Blocks/report6.i >> TimeFiles/BU/time6-20-b.i

make clean