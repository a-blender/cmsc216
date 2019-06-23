#!/bin/sh
# this script runs the public tests on the d8sh shell
# all public tests are located in the ~/216/project6/testing folder

# run the makefile
echo "Running the makefile..."
make

# copy executable into testing and move there
cp ./d8sh ~/216/project6/testing
cd ~/216/project6/testing

# run the first set of public tests, due on april 28
echo "Running public tests due on april 28..."

echo "Running public test 0..."
d8sh < public00.in > results0
diff results0 public00.output

echo "Running public test 1..."
d8sh < public01.in > results1
diff results1 public01.output

echo "Running public test 2..."
d8sh < public02.in > results2
diff results2 public02.output

echo "Running public test 6..."
d8sh < public06.in > results6
diff results6 public06.output

echo "Running public test 7..."
d8sh < public07.in > results7
diff results7 public07.output

echo "Running public test 11..."
d8sh < public11.in > results11
diff results11 public11.output

# run the second set of public tests due may 2
echo "Running public tests due on may 2..."

echo "Running public test 3..."
d8sh < public03.in > results3
diff results3 public03.output

echo "Running public test 4..."
d8sh < public04.in > results4
diff results4 public04.output

echo "Running public test 5..."
d8sh < public05.in > results5
diff results5 public05.output

echo "Running public test 8..."
d8sh < public08.in > results8
diff results8 public08.output

echo "Running public test 9..."
d8sh < public09.in > results9
diff results9 public09.output

echo "Running public test 10..."
d8sh < public10.in > results10
diff results10 public10.output

echo "Running public test 12..."
d8sh < public12.in > results12
diff results12 public12.output

echo "Running public test 13..."
d8sh < public13.in > results13
diff results13 public13.output

# clean up your temp files from the testing dir
echo "Cleaning up testing files..."
echo "Success - thank you!"
rm -f ./*~ ./results* ./d8sh


