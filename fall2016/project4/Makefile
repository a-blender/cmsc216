#Anna Blendermann, ablender, 114474025, 0104
# I pledge on my honor that I have not received any unauthorized assistance
# on this programming assignment (project4)

# this is a simple Makefile to compile the available project4 files
# into the executable fs-sim.x

CFLAGS = -ansi -pedantic-errors -Wall -Werror -Wshadow -Wwrite-strings -g

all: public01.x public02.x public03.x public04.x public05.x public06.x/
	public07.x public08.x public09.x public10.x

public01.x: public01.o fs-sim.o
	gcc public01.o fs-sim.o -o public01.x

public02.x: public02.o fs-sim.o
	gcc public02.o fs-sim.o -o public02.x

public03.x: public03.o fs-sim.o memory-checking.o
	gcc public03.o fs-sim.o memory-checking.o -o public03.x

public04.x: public04.o fs-sim.o memory-checking.o
	gcc public04.o fs-sim.o memory-checking.o -o public04.x

public05.x: public05.o fs-sim.o driver.o memory-checking.o
	gcc public05.o fs-sim.o driver.o memory-checking.o -o public05.x

public06.x: public06.o fs-sim.o
	gcc public06.o fs-sim.o -o public06.x

public07.x: public07.o fs-sim.o
	gcc public07.o fs-sim.o -o public07.x

public08.x: public08.o fs-sim.o
	gcc public08.o fs-sim.o -o public08.x

public09.x: public09.o fs-sim.o driver.o
	gcc public09.o fs-sim.o driver.o -o public09.x

public10.x: public10.o fs-sim.o driver.o
	gcc public10.o fs-sim.o driver.o -o public10.x

fs-sim.o: fs-sim.c fs-sim.h
	gcc $(CFLAGS) -c fs-sim.c

public01.o: public01.c fs-sim-datastructure.h fs-sim.h
	gcc $(CFLAGS) -c public01.c

public02.o: public02.c fs-sim.h
	gcc $(CFLAGS) -c public02.c

public03.o: public03.c fs-sim.h memory-checking.h
	gcc $(CFLAGS) -c public03.c

public04.o: public04.c fs-sim.h memory-checking.h
	gcc $(CFLAGS) -c public04.c

public05.o: public05.c fs-sim.h driver.h memory-checking.h
	gcc $(CFLAGS) -c public05.c

public06.o: public06.c fs-sim.h
	gcc $(CFLAGS) -c public06.c

public07.o: public07.c fs-sim.h
	gcc $(CFLAGS) -c public07.c

public08.o: public08.c fs-sim.h
	gcc $(CFLAGS) -c public08.c

public09.o: public09.c fs-sim.h driver.h
	gcc $(CFLAGS) -c public09.c

public10.o: public10.c fs-sim.h driver.h
	gcc $(CFLAGS) -c public10.c

clean:
	echo "Removing compiler-generated files";
	rm -r public01.x public02.x public03.x public04.x public05.x/
	public06.x public07.x public08.x public09.x public10.x fs-sim.o/
	public01.o public02.o public03.o public04.o public05.o public06.o/
	public07.o public08.o public09.o public10.o
