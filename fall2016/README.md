# cmsc216
Computer Systems | University of Maryland College Park | Fall 2016

Project 1: Linecheck

This is a simple C program that checks the string output from files. Specifically, the program checks whether each line size exceeds 80 chars, counts the number of lines, and then prints the output. 

Project 2: Machine Instructions

This is a simple C program that reads and outputs machine instructions by converting them from machine code into assembly. This program uses a custom C struct to store assembly instructions. 

Functions:

- assemble: assembles a machine code instruction into assembly 
- valid_instruction: validates an assembly instruction
- print_instruction: prints an assembly instruction struct
- disasemble: disasembles an assembly instruction into machine code

Project 3-4: UNIX Filesystem

This is a C program that simulates a UNIX filesystem with five simple commands: touch, mkdir, cd, ls, and pwd. This program uses the Fm-sim and Directory structures to build a working filesystem.

You can think of this system as an incomplete tree, where the top Node is the root directory. Each level of the tree contains a linked list of directories, and each directory has pointer to its parent/sub folders.

Project 5: TA List 

This is a C program that uses a singly-linked list to keep track of unique IDs and salaries for Computer Science TAs. Program function includes recursive list interation, addition, removal, and data output.

Project 6: Mockfile 

This is a C program that implements a custom Mockfile structure that contains a singly-linked list of Target structures. The Mockfile structure has references to both its head and tail Targets. The program implements list iteration to read data, recursive searching, and data removal.

Project 7: C to Assembly 

This project contains two C programs converted into MIPS Assembly code (opcodes, registers), with storage efficiency as the primary goal. This was done solely for the sake of academic suffering. If you actually need to convert C to Assembly, use this website: https://godbolt.org/. Good luck!

Programs:

- prog1: reverses the characters of a number, and negates the number before and after reversal, if it's negative
- prog2: stores input values into an array, and then counts the instances of one element in the array, using size and start value
