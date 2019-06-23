# Project #6 public tests makefile

CC = gcc
CFLAGS= -g -ansi -pedantic-errors -Wall -Werror -Wshadow -Wwrite-strings

# create all public tests

all: public01.x public02.x public03.x public04.x public05.x \
     public06.x public07.x public08.x public09.x public10.x

# link object files to form executables

public01.x: public01.o mockfile.o split.o safe-fork.o
	$(CC) public01.o mockfile.o split.o safe-fork.o -o public01.x

public02.x: public02.o mockfile.o split.o safe-fork.o
	$(CC) public02.o mockfile.o split.o safe-fork.o -o public02.x 

public03.x: public03.o mockfile.o split.o safe-fork.o
	$(CC) public03.o mockfile.o split.o safe-fork.o -o public03.x

public04.x: public04.o mockfile.o split.o safe-fork.o
	$(CC) public04.o mockfile.o split.o safe-fork.o -o public04.x

public05.x: public05.o mockfile.o split.o safe-fork.o memory-checking.o
	$(CC) public05.o mockfile.o split.o safe-fork.o memory-checking.o \
              -o public05.x 

public06.x: public06.o mockfile.o split.o safe-fork.o memory-checking.o
	$(CC) public06.o mockfile.o split.o safe-fork.o memory-checking.o \
              -o public06.x 

public07.x: public07.o mockfile.o make-target.o split.o safe-fork.o
	$(CC) public07.o mockfile.o make-target.o split.o safe-fork.o \
              -o public07.x

public08.x: public08.o mockfile.o make-target.o split.o safe-fork.o
	$(CC) public08.o mockfile.o make-target.o split.o safe-fork.o \
              -o public08.x

public09.x: public09.o mockfile.o make-target.o split.o safe-fork.o
	$(CC) public09.o mockfile.o make-target.o split.o safe-fork.o \
              -o public09.x 

public10.x: public10.o mockfile.o make-target.o split.o safe-fork.o
	$(CC) public10.o mockfile.o make-target.o split.o safe-fork.o \
              -o public10.x 

# create object files

public01.o: public01.c mockfile.h mockfile-datastructure.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c mockfile.h mockfile-datastructure.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c mockfile.h mockfile-datastructure.h
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c mockfile.h mockfile-datastructure.h
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c mockfile.h mockfile-datastructure.h memory-checking.h
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c mockfile.h mockfile-datastructure.h memory-checking.h
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c mockfile.h mockfile-datastructure.h make-target.h
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c mockfile.h mockfile-datastructure.h make-target.h
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c mockfile.h mockfile-datastructure.h make-target.h
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c mockfile.h mockfile-datastructure.h make-target.h
	$(CC) $(CFLAGS) -c public10.c

mockfile.o: mockfile.c mockfile.h mockfile-datastructure.h split.h safe-fork.h
	$(CC) $(CFLAGS) -c mockfile.c

clean:
	rm -f public*.o public*.x mockfile.o
