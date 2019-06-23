CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow \
         -pedantic-errors -fstack-protector-all 
PROGS = user_interface public01 public02 public03 public04 public05 \
	public06 public07 public08 public09

.PHONY: all clean

all: $(PROGS)

clean:
	rm -f *.o $(PROGS) *.tmp

$(PROGS): document.o
user_interface: user_interface.o
public%: public%.o

user_interface.o: document.h
document.o: document.h
public%.o: document.h
