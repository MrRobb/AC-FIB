.text
   .align 4
   .globl BuscarElemento
   .type BuscarElemento,@function

BuscarElemento:

		pushl	%ebp
		movl	%esp, %ebp

		# v[*mid].k
		movl	16(%ebp), %eax
		movl	(%eax), %eax
		movl	32(%ebp, %eax, $4), %eax
		movl	(%eax), %eax

		# X.k -> 24(%ebp)
		# comparar v[*mid].k, X.k
		compl	24(%ebp), %eax
		jne		else1

if1:	# sentencia if1 -> return * mid
		movl	16(%ebp), %eax
		movl	(%eax), %eax
		jmp 	endif1

else1:	# sentencia else1 -> tot el pedazo de codi

		# *mid
		movl	16(%ebp), %eax
		movl	(%eax), %eax

		# *high
		movl	12(%ebp), %ecx
		movl	(%ecx), %ecx

		#comparar *mid, *high
		compl	%ecx, %eax
		jge 	else2

if2:	# sentencia if2 -> * mid = * high; (* low)++;
		movl	16(%ebp), %eax		# &mid
		movl 	%ecx, (%eax)		# *mid = * high
		movl 	8(%ebp), %edx		# &low
		movl	(%edx), %edx		# *low
		incl	%edx				# (*low) + 1
		movl 	8(%ebp), %ecx		# &low
		movl	%edx, (%ecx)		# *low = (*low) + 1
		jmp 	endif2

else2:	# sentencia else2 -> * mid = * low; (* high)--;
		movl 	8(%ebp), %edx		# &low
		movl	(%edx), %edx		# *low
		movl	16(%ebp), %eax		# &mid
		movl 	%edx, (%eax)		# *mid = * low
		decl	%ecx				# (*high) - 1
		movl	12(%ebp), %edx		# &high
		movl	%ecx, (%edx)		# *high = (*high) - 1

endif2:	# sentencia despres de else -> return -1;
		movl 	$-1, %eax

endif1:
		ret
		movl 	%ebp, %esp
		popl 	%ebp
