CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow \
-pedantic-errors -fstack-protector-all 
PUBTESTS = public01 public02 public03 public04 public05 public06

.PHONY: all clean backup

all: $(PUBTESTS)

clean:
	rm -f *.o $(PUBTESTS) a.out

$(PUBTESTS): document.o

public%: public%.o

document.o: document.h
public%.o: document.h

