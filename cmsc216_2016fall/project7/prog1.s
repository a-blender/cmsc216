# Anna Blendermann, ablender, 114474025, 0104
# This is a MIPS Assembly program to written to imitate prog1.c
	
# This function reverses the characters of a number, and
# negates the number before and after reversal, if it's negative
	
		.data
n:		.word 0	
reversed: 	.word 0
negative:	.word 1
newline:	.asciiz "\n"
		.text

# MAIN FUNCTION*****************************************************************
# this function scans in a number, then uses a while loop to reverse
# the characters, using negation to avoid affecting modulus
	
main:	# this is now the body of the function int main()
	li $v0, 5
	syscall
	sw $v0, n		# scanf("%d", &n)

	lw $t0, n		# load n into t0 (compare)
	
	# if statement that negates n if n < 0
	ble $t0, 0, continue	# if(n < 0)
	li $t1, -1
	sw $t1, negative	# negative = -1
	mul $t0, $t0, -1
	sw $t0, n		# n = -n
	
continue:
	lw $t0, n		# load n into t0 again

loop:	# while loop that reverses n if n > 0
	bge $t0, 0, exit

	lw $t1, reversed
	mul $t1, $t1, 10
	sw $t1, reversed	# reversed *= 10

	lw $t1, reversed
	rem $t2, $t0, 10
	add $t1, $t1, $t2	# add reversed and remainder of n%10
	sw $t1, reversed	# reverse += n % 10

	div $t0, $t0, 10
	sw $t0, n		# n /= 10

	jal loop		# jump back to top of loop

exit:	# out of the while loop now, three statements left
	lw $t0, reversed
	lw $t1, negative
	mul $t0, $t0, $t1
	sw $t0, reversed	# reversed *= negative

	lw $t0, reversed	# load reversed again to print it
	li $v0, 1
	move $a0, $t0
	syscall			# printf("%d", reversed)

	li $v0, 4
	la $a0, newline
	syscall			# printf("\n")

	li $v0, 10		# return 0, aka quit program
	syscall

	
	
	
