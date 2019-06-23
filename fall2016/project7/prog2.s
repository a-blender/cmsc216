# Anna Blendermann, ablender 114474025, 0104
# This is a MIPS Assembly program written to imitate prog2.c
	
# This function stores input values into an array, and then counts the
# the instances of one element in the array, using size and start value

		.data
arr:		.word 0:100	# array of 100 elements
x:		.word 0		# int x
size:		.word 0		# int size
element:	.word 0		# int element
start:		.word 0		# int start
newline:	.asciiz "\n"
		.text

# MAIN FUNCTION***************************************************************
# this function stores input values into the array, and then calls count()
# to find instances of one element, before printing the return value
main:	li $sp, 0x7ffffffc

	li $v0, 5
	syscall
	sw $v0, x		# scanf("%d", &x)
	
loop:	# while loop that scans numbers into the array
	# load x into t0 and size into t1
	lw $t0, x
	lw $t1, size

	beq $t0, 0, endloop 	# while (x != 0)
	bge $t1, 100, skipif	# if (size < 100)

	mul $t4, $t1, 4		# calculate memory offest for arr[size]
	sw $t0, arr($t4)	# arr[size] = x
	
	add $t1, $t1, 1
	sw $t1, size		# size++
	
skipif:	# out of if-statement, still in while loop
	li $v0, 5
	syscall
	sw $v0, x		# scan("%d", &x)
	
	sw $t1, size		# store size again
	j loop			# jump to top of the while loop

endloop:
	# OUT OF THE WHILE LOOP NOW: CONTINUE WITH MAIN()
	# execute the next two scanfs, for element and start
	li $v0, 5
	syscall
	sw $v0, element		# scanf("%d", &element)
	
	li $v0, 5
	syscall
	sw $v0, start		# scan("%d", &start)
	
	# sweet, we got this far! Now to call count()
	# remember, to gotta push/pop the args onto/from the stack

	lw $t1, size		# push size onto the stack
	sw $t1, ($sp)
	sub $sp, $sp, 4
	
	lw $t2, element		# push element onto the stack
	sw $t2, ($sp)
	sub $sp, $sp, 4
	
	lw $t3, start		# push start onto the stack
	sw $t3, ($sp)
	sub $sp, $sp, 4

	jal count		# CALL COUNT() FUNCTION

	# now print the contents of the count() function
	# remember, the return value will be in v0
	move $a0, $v0		# move return value to a0
	li $v0, 1
	syscall			# printf("%d\n", count(size, element, start))

	li $v0, 4
	la $a0, newline
	syscall			# printf("\n")	

	add $sp, $sp, 12 	# pop all three args from the stack
	li $v0, 10
	syscall			# return 0, quit program

# COUNT FUNCTION***************************************************************
# provided the params are valid, this function iterates through the array
# to find instances of the same element, then returns that value
# invalid parameters = return -1 in the $v0 register	

count:	sub $sp, $sp, 16	# setup the stack pointer
	sw $ra, 16($sp)		# save the return address of stack pointer
	sw  $fp 12($sp)		# save the old frame pointer
	add $fp, $sp, 16	# set new frame pointer
	
	# finished setting up stack and frame pointers
	# remember, we have max -> 12($fp), value -> 8($fp), from -> 4($fp) 
	# remember, we have i at 4($sp) and "answer" at 8($sp)

	li $t5, 0
	sw $t5, 4($sp)		# int i
	
	li $t6, 0
	sw $t6, 8($sp)		# int answer = 0
	
	lw $t7, 12($fp)		# load max into t7
	lw $t8, 8($fp)		# load value into t8
	lw $t9, 4($fp)		# load from into t9

	# one condition is true = jump to if, otherwise jump to else
	blt $t7, 0, if		# if (max < 0)
	blt $t9, 0, if		# if (from < 0)
	bge $t9, $t7, if	# if (from >= max)
	j else
	
if:	li $t6, -1		# load -1 into t2
	sw $t6, 8($sp)		# answer = -1
	
	j  skip			# skip else block, to end of function
	
else:	# WRITE THE ELSE BLOCK HERE
	lw $t5, 4($fp)
	sw $t5, 4($sp)		# i = from (part1 of for loop)

CNTLP:	lw $t5, 4($sp)
	bge $t5, $t7, skip	# if (i < max) (part2 of for loop)
	
	mul $t4, $t5, 4		# calculate offset for arr[i]
	lw $t4, arr($t4)	# load arr[i] back into t2

	bne $t4, $t8, endif	# if (arr[i] == value)
	lw $t6, 8($sp)		# load answer into t0
	add $t6, $t6, 1
	sw $t6, 8($sp)		# answer++	

endif:	lw $t5, 4($sp)
	add $t5, $t5, 1
	sw $t5, 4($sp)		# i++ (part3 of for loop)

	j CNTLP			# Jump back to top of loop

skip:	# passed if-else statement, now return answer
	move $v0, $t6		# return answer

	# done with body of count(), now function teardown
	lw $ra, 16($sp)		# restore the stack pointer address
	lw $fp, 12($sp)		# restore the frame pointer address
	add $sp, $sp, 16	# reset stack pointer
	jr $ra			# return to original caller using saved address
	
	
