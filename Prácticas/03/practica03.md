```c
#define N 10
int Matriz[N][N];
int i;
int suma;

for (i = 0, suma=0; i < N; i++)
	suma += Matriz[3][i];
```

## 1

```assembly
			movl $0, %eax	# i = 0
			movl $0, %ebx	# suma = 0

for:	cmpl $10, %eax
			jge endfor

			addl Matriz($120, %eax, $4), %ebx

			incl %eax
			jmp for

endfor:
			movl %ebx, suma
```

2 + 5 * 10 + 2 + 1

> Matriz[3][i] = @Matriz + (3*10 + i)* 4 = @Matriz + 4(30 + i) = @Matriz + 120 + 4i

## 2

```assembly
			movl $0, %ebx	# suma = 0
			leal Matriz($120), %ecx		# &Matriz[3][0]
			leal Matriz($160), %edx		# &Matriz[3][10]

for:	cmpl %edx, %ecx
			jge endfor

			addl (%ecx), %ebx

			addl %ecx, $4
			jmp for

endfor:
			movl %ebx, suma
```

3 + 5 * 10 + 2 + 1

## 3

```c
#define N 10
#define M 100

int Matriz[10][10];
int ResFila[10];

for(int i = 0; i < 10; i++)
{
	ResFila[i] = 1;
	int j = 0;
	while(Matriz[i][j] != 0)
	{
		if (Matriz[i][j] == 100)
			ResFila[i] * = Matriz[i][j];
		j++;
	}
}
```

```assembly
		movl $0, %esi	# i = 0
for:	cmpl $10, %esi
			jge endfor
			movl $0, %ebx	# j = 0
			movl $1, (Resfila, %esi, $4)		# ResFila[i] = 1

while:	movl (Matriz, %esi, $40), %ecx
			addl (, %ebx, $4), %ecx			# Matriz[i][j]
			cmpl $0, %ecx
			je endwhile

			cmpl $100, %ecx
			jne endif

			movl (Resfila, %esi, 4), %eax
			imull (%ecx)
			movl %eax, (Resfila, %esi, 4)

endif:			

			incl %ebx
			jmp while

endwhile:

			incl %esi
			jmp for

endfor:

```

## 1

```c++
int OperaVec(int Vector[], int elementos)
{
    // La @ de Vector esta en la @ 8[ebp] y el
    // valor de la variable elementos en la @ 12[ebp]
    int i;  // i esta en la @ -8[ebp]
    int res; // res esta en la @ -4[ebp]
		res=Vector[0];
		// Código que has de introducir
		for (i = 1; i < elementos; i++)
			if (Vector[i]<res)
    			res = Vector[i];
		// Fin del código a introducir
		return res;
}
```

```c
.text
	.align 4
	.globl OperaVec
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
// Aqui has de introducir el codigo
	movl	$1, %ecx		// ecx = 1 (= i)

for:
	cmpl	12(%ebp), %ecx
	jge		endfor

	movl	8(%ebp, %ecx, 4), %edx		//Vector[i]
	cmpl -4(%ebp), %edx
	jge endif
	movl %edx, -4(%ebp)							// res = Vector[i];
endif:

	incl %ecx
	jmp for
endfor:

	movl %ecx, -8(%ebp)	// i = ecx
// El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
```

## 2

```c
#define N 3
int OperaMat(int Matriz[N][N], int salto) {
	// La @ de Matriz esta en la @ 8[ebp] y el
	// valor de la variable salto en la @ 12[ebp]
	int j; 		// j esta en la @ -12[ebp]
	int i;  	// i esta en la @ -8[ebp]
	int res; 	// res esta en la @ -4[ebp]
	// Codigo que has de introducir
	res=0;
	for (i=0; i <3; i+=salto) {
		for (j=0; j <3; j++) {
			res -= Matriz[i][i] + j;
		}
	}
	// Fin del codigo a introducir
	return res;
}
```

```c
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
	movl $0, -4(%ebp)
	movl $0, -8(%ebp)
for1:
	cmpl $3, -8(%ebp)		// comp 3, i
	jge endfor

	movl $0, -12(%ebp)	// j = 0

for2:
	cmpl $3, -12(%ebp)	// comp 3, j
	jge endfor2

	// &Matriz + (i * 3 + i) * 4 = &Matriz + (i * 16)
	movl -8(%ebp), %eax
	movl 8(%ebp, %eax, 16), %eax
	addl -12(%ebp), %eax				// %eax = Matriz[i][i] + j
	subl %eax, -4(%ebp)					// res -= %eax

	//incremento for2
	incl -12(%ebp)

endfor2:

	//incremento for1
	movl -12(%ebp), %edx
	addl %edx, -8(%ebp)

endfor1:
# El final de la rutina ya esta programado
	movl	-4(%ebp), %eax
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
```
