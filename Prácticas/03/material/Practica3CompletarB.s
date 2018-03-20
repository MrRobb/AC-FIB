.text
	.align 4
	.globl OperaMat
	.type	OperaMat, @function
OperaMat:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
# Aqui has de introducir el codigo
	movl 	$0, -4(%ebp)
	movl 	$0, -8(%ebp)
for1:
	cmpl 	$3, -8(%ebp)		# comp 3, i
	jge 	endfor
	movl 	$0, -12(%ebp)	# j = 0
for2:
	cmpl 	$3, -12(%ebp)	# comp 3, j
	jge 	endfor2
	# &Matriz + (i * 3 + i) * 4 = &Matriz + (i * 16)
	movl 	-8(%ebp), %eax
	movl 	8(%ebp, %eax, 16), %eax
	addl 	-12(%ebp), %eax				# %eax = Matriz[i][i] + j;
	subl 	%eax, -4(%ebp)					# res -= %eax
	# incremento for2
	incl 	-12(%ebp)
endfor2:
	# incremento for1
	movl 	-12(%ebp), %edx
	addl 	%edx, -8(%ebp)
endfor1:
# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx	
	movl %ebp,%esp
	popl %ebp
	ret
