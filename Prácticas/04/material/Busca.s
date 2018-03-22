.text
 .align 4
 .globl Buscar
 .type Buscar,@function
Buscar:
			pushl	%ebp
			movl	%esp, %ebp

			movl 	$-1, -4(%ebp)			# trobat = -1
			movl 	$0, -16(%ebp)			# low = 0
			movl 	$0, -8(%ebp)			# mid = low
			movl 	24(%ebp), %ecx			# N
			decl	%ecx					# N-1
			movl	%ecx, -12(%ebp)			# high = N-1

while:		movl	-12(%ebp), %ecx			# high
			compl	%ecx, -16(%ebp)			# comparar high, low
			jg		endwhile

			# preparar pila per fer call de BuscarElemento
			pushl	8(%ebp)					# &v
			pushl	20(%ebp)				# X.m
			pushl	16(%ebp)				# X.k
			pushb 	12(%ebp)				# X.c
			leal	-8(%ebp), %ecx
			pushl	%ecx					# &mid
			leal	-12(%ebp), %ecx
			pushl	%ecx					# &high
			leal	-16(%ebp), %ecx
			pushl	%ecx					# &low

			# llamada
			call BuscarElemento

			addl $28, %ebp

			# eax ya esta en eax

			compl	$0, %eax
			jl		endwhile
			jmp while
endwhile:
			ret
			movl 	%ebp, %esp
			popl 	%ebp
