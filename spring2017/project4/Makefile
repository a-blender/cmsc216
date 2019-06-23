# MAKEFILE by Anna Blendermann
# this makefile compiles and links the project4 source files
CFLAGS = -ansi -Wall -g -O0 -Werror -Wshadow -Wwrite-strings \
-pedantic-errors -fstack-protector-all

# create all public and student test targets
all: public01 public02 public03 public04 public05 student_tests

# create executables for the public tests
public01: calendar.o public01.o my_memory_checker_216.o
	gcc calendar.o public01.o my_memory_checker_216.o -o public01

public02: calendar.o public02.o my_memory_checker_216.o
	gcc calendar.o public02.o my_memory_checker_216.o -o public02

public03: calendar.o public03.o my_memory_checker_216.o
	gcc calendar.o public03.o my_memory_checker_216.o -o public03

public04: calendar.o public04.o my_memory_checker_216.o
	gcc calendar.o public04.o my_memory_checker_216.o -o public04

public05: calendar.o public05.o my_memory_checker_216.o
	gcc calendar.o public05.o my_memory_checker_216.o -o public05

# create an executable for my student_tests.c source file
student_tests: student_tests.o my_memory_checker_216.o
	gcc student_tests.o my_memory_checker_216.o -o student_tests

# compile the five public tests into object files
public01.o: public01.c event.h calendar.h
	gcc $(CFLAGS) -c public01.c

public02.o: public02.c event.h calendar.h
	gcc $(CFLAGS) -c public02.c

public03.o: public03.c event.h calendar.h
	gcc $(CFLAGS) -c public03.c

public04.o: public04.c event.h calendar.h
	gcc $(CFLAGS) -c public04.c

public05.o: public05.c event.h calendar.h
	gcc $(CFLAGS) -c public05.c

# compile other source files into object files
student_tests.o: student_tests.c event.h calendar.h	
	gcc $(CFLAGS) -c student_tests.c -o student_tests.o

calendar.o: calendar.c calendar.h
	gcc $(CFLAGS) -c calendar.c -o calendar.o

my_memory_checker_216.o: my_memory_checker_216.c my_memory_checker_216.h
	gcc $(CFLAGS) -c my_memory_checker_216.c -o my_memory_checker_216.o

# clean: delete all object files and executables
clean:
	echo "Cleaning project4 files"
	rm public01 public02 public03 public04 student_tests ./*.o








