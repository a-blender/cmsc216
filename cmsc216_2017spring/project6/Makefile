# MAKEFILE by Anna Blendermann
# this makefile compiles and links the project6 source files
# there are two sets, parser source files and shell source files
CFLAGS = -ansi -Wall -g -O0 -Werror -Wshadow -Wwrite-strings \
-pedantic-errors -fstack-protector-all

# call the target for the shell executable
all: d8sh

# create the shell executable by linking the object files
d8sh: d8sh.o executor.o parser.tab.o lexer.o
	gcc -lreadline d8sh.o executor.o parser.tab.o lexer.o -o d8sh

# compile the shell source files into object files
d8sh.o: d8sh.c executor.h lexer.h
	gcc $(CFLAGS) -c d8sh.c

executor.o: executor.c executor.h command.h
	gcc $(CFLAGS) -c executor.c

# compile the parser source files into object files
parser.tab.o: parser.tab.c command.h
	gcc $(CFLAGS) -c parser.tab.c

lexer.o: lexer.c
	gcc $(CFLAGS) -c lexer.c

# clean: delete all object files and executables
clean:
	echo "Cleaning project6 files"
	rm -f d8sh ./*~ ./*.o








