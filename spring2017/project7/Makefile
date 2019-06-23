# MAKEFILE by Anna Blendermann
# compiles the source files from project7

CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

# all target runs all the public test executables
all: public01 public02 public03 public04

# create executables for all the public tests
public01: public01.o bag.o
	gcc public01.o bag.o -o public01

public02: public02.o bag.o
	gcc public02.o bag.o -o public02

public03: public03.o bag.o
	gcc public03.o bag.o -o public03

public04: public04.o bag.o my_memory_checker_216.o
	gcc public04.o bag.o my_memory_checker_216.o -o public04

tester: bag.o tester.o
	gcc bag.o tester.o -o tester

# create object files for the public tests
public01.o: public01.c bag.h bag-implementation.h
	gcc $(CFLAGS) -c public01.c

public02.o: public02.c bag.h
	gcc $(CFLAGS) -c public02.c

public03.o: public03.c bag.h
	gcc $(CFLAGS) -c public03.c

public04.o: public04.c bag.h my_memory_checker_216.h
	gcc $(CFLAGS) -c public04.c

# create object file for the bag implementation
bag.o: bag.c bag.h bag-implementation.h
	gcc $(CFLAGS) -c bag.c

my_memory_checker_216.o: my_memory_checker_216.c my_memory_checker_216.h
	gcc $(CFLAGS) -c my_memory_checker_216.c

tester.o: bag.c tester.c bag.h
	gcc $(CFLAGS) -c bag.c tester.c

# clean deletes all object files and executables
clean:
	echo "Removing project files..."
	rm -f ./*~ ./*.o public01 public02 public03 public04 tester


