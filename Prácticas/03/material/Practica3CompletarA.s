.text
	.align 	4
	.globl 	OperaVec
	.type	OperaVec, @function
OperaVec:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
# Aqui has de introducir el codigo
	movl	$1, %ecx		// ecx = 1 (= i)
for:
	cmpl	12(%ebp), %ecx
	jge		endfor
	movl	8(%ebp, %ecx, 4), %edx		//Vector[i]
	cmpl	-4(%ebp), %edx
	jge		endif
	movl	%edx, -4(%ebp)							// res = Vector[i];
endif:
	incl	%ecx
	jmp		for
endfor:
	movl	%ecx, -8(%ebp)	// i = ecx
# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx
	movl 	%ebp,%esp
	popl 	%ebp
	ret
