# 1.
##  Buscad para qué sirven y qué operandos admiten las instrucciones psubb, pcmpgtb, movdqa, movdqu y emms.

###### PSUBB (Packet - Subtract - Byte)

Subtract packed byte integers in mm/m64 from packed byte integers in mm.

###### PCMPGTB (Packet - Compare greater than - Byte)

Compare packed signed byte integers in mm and mm/m64 for greater than.

###### MOVDQA (Move - Double Quadword Aligned)

Moves a double quadword from the source operand (second operand) to the destination operand (first operand).

###### MOVDQU (Move - Double Quadword Unaligned)

Moves a double quadword from the source operand (second operand) to the destination operand (first operand).

###### EMMS (Empty MMX State)

Using EMMS is like emptying a container to accommodate new content.
The EMMS instruction sets the values of the floating-point (FP) tag word to empty (all ones).

```
https://docs.oracle.com/cd/E18752_01/html/817-5477/eojdc.html // shitty
https://x86.puri.sm/ // super cool
```

# 2.
## Buscad para qué sirve y cómo se usa en C la propiedad _\_attribute\_\_ y el atributo aligned.

_\_attribute\_\_ is a compiler directive that specifies characteristics on declarations, which allows for more error checking and advanced optimizations.

```c
char *__attribute__((aligned(8))) *f;
```

aligned: specifies a minimum alignment (bytes) for variables of the specified type. It forces the compiler to maintain this.
Example:

```c
struct S { short f[3]; } __attribute__ ((aligned (8)));
typedef int more_aligned_int __attribute__ ((aligned (8)));
```

# 3.
## Programad en ensamblador sin usar instrucciones SSE una versión de la rutina que hay en Procesar.c procurando hacerla lo más rápida posible (1 solo bucle, acceso secuencial...):

```c
void procesar(unsigned char *mata, unsigned char *matb, unsigned char *matc, int n)
{
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			matc[i*n+j]=(mata[i*n+j] - matb[i*n+j]);
			if (matc[i*n+j]>0) matc[i*n+j]=255;
			else matc[i*n+j]=0;
		}
	}
}
```

```assembly
.text
	.align 4
	.globl procesar
	.type	procesar, @function
procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx		
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo
		movl $0, %eax		# eax = i = 0
		movl 8(%ebp), %ebx	# ebx = @mata
		movl 12(%ebp), %ecx	# ecx = @matb
		movl 16(%ebp), %edi	# edi = @matc
		movl 20(%ebp), %esi	# esi = n
		imull %esi, %esi	# esi = nxn -> solo un bucle

for:
		cmpl %esi, %eax
		jge endfor			# saltar si i >= n*n

		movl (%ecx), %edx
		subl (%ebx), %edx	# mata[i*n+j] - matb[i*n+j]
		movl %edx, (%edi)	# matc[i*n+j] = mata[i*n+j] - matb[i*n+j]


		cmpl $0, %edx
		jle else
if:
		movl $255, (%edi)	# matc[i*n+j]
		jmp endif

else:
		movl $0, (%edi)		# matc[i*n+j]

endif:
		addl $16, %eax		# i = i + 16;
		addl $16, %ebx		# stride
		addl $16, %ecx		# stride
		addl $16, %edi		# stride
		jmp for

endfor:

# El final de la rutina ya esta programado

	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
```

# 4.
## Explicad como se puede cargar un valor inmediato en un registro xmm usando la instrucción movdqu.

| Mnemonic               | Description                                           |
|------------------------|-------------------------------------------------------|
| MOVDQU xmm1, xmm2/m128 | Move unaligned double quadword from xmm2/m128 to xmm1 |
| MOVDQU xmm2/m128, xmm1 | Move unaligned double quadword from xmm1 to xmm2/m128 |

# 5.
## Programad en ensamblador una versión SIMD de la rutina que hay en Procesar.c usando las instrucciones psubb, pcmpgtb y movdqu.

```assembly
.text
	.align 4
	.globl procesar
	.type	procesar, @function
zero:   .byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx		
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo
		movl $0, %eax		# eax = i = 0
		movl 8(%ebp), %ebx	# ebx = @mata
		movl 12(%ebp), %ecx	# ecx = @matb
		movl 16(%ebp), %edi	# edi = @matc
		movl 20(%ebp), %esi	# esi = n
		imull %esi, %esi	# esi = nxn -> solo un bucle

for:
		cmpl %esi, %eax
		jge endfor			# saltar si i >= n*n

		movdqu (%ebx), %xmm0	# xmm0 = mata[i*n+j]
		movdqu (%ecx), %xmm1	# xmm1 = matb[i*n+j]
		psubb %xmm1, %xmm0	# xmm0 = mata[i*n+j] - matb[i*n+j]
		movdqu %xmm0, (%edi)	# matc[i*n+j] = mata[i*n+j] - matb[i*n+j]

		movdqu cero, %xmm2	# xmm2 = 0
		pcmpgtb %xmm2, %xmm0
		movdqu %xmm0, (%edi)

endif:
		addl $16, %eax		# i = i + 16;
		addl $16, %ebx		# stride
		addl $16, %ecx		# stride
		addl $16, %edi		# stride
		jmp for

endfor:

# El final de la rutina ya esta programado

	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
```

# 6.
## Escribid un código en ensamblador que, a partir de un valor almacenado en un registro, averigüe si es multiplo de 16.

```assembly
	andl 0x0000000F, %eax
	jne no_multiplo

multiplo:
	# es multiplo

no_multiplo:
	# no es multiplo

fin:
```
