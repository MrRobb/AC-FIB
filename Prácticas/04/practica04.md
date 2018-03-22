...c
kkkk
mmmm

### Buscar

```c
int Buscar(S1 v[], S1 X, int N){

   int low, high, mid;
   int trobat = -1;

   low = 0;
   mid = low;
   high = N-1;
   while (low <= high) {
 	trobat = BuscarElemento(&low, &high, &mid, X, v);
	if (trobat >= 0) break;
   }

   return trobat;
}
```

low		-16
high	-12
mid		-8
trobat	-4
%ebp	+0
@ret	+4
&v		+8
X		+12
N		+24
		+28

### BuscarElemento

```c
int BuscarElemento(int *low, int *high, int *mid, S1 X, S1 v[])
{  
  if (X.k == v[*mid].k)
    return *mid;	/* elemento encontrado * /
  else
    if (*mid < *high) {
      * mid = * high;
      (* low)++;
    } else {
      * mid = * low;
      (* high)--;
    }
  return -1;            /* elemento no encontrado * /
}
```

%ebp	0
@ret	+4
&low	+8
&high	+12
&mid	+16
X		+20
&v		+32
		+36

### Main

```c
int main(int argc, char *argv[])
{  
   int a=1, b=27;
   int n;
   int trobat;
   S1 X = {'Z', 310, &a};
   S1 Y = {'Z',   6, &a};
   S1 Z = {'Z',  30, &a};
   S1 v[30] = {{'3', 13, &a}, {'r', 97, &b}, {'y',  0, &a}, {'8', 48, &b},
               {'x', 17, &a}, {'z', 41, &b}, {'p', -3, &a}, {'$', 62, &b},
               {'r',  3, &a}, {'+', 37, &b}, {'y',  6, &a}, {'%', -9, &b},
               {'g',  5, &a}, {'b',  1, &b}, {'m', 12, &a}, {'q', 32, &b},
               {'!',  7, &a}, {'-',  2, &b}, {'i', 25, &a}, {'z', 32, &b},
               {' ', 0x80000000, NULL}};
}
```

a		-412
b		-408
n		-404
trobat	-400
X		-396
Y		-384
Z		-372
v[0]	-360
...		...
v[29]	-12
%ebp	+0
@ret	+4
argc	+8
argv	+12

### SencillaSub

```c
int SencillaSub(S1 a, char b)
{
	int i;
	if (a.c == b) i = 0;
	else i = * (a.m);
	return i + a.k;
}
```

i		-4
%ebp	+0
@ret	+4
a		+8
b		+20
		+21

```assembly
		pushl	%ebp
		movl	%esp, %ebp
		# espacio para guardar i
		movb	8(%ebp), %al			# 8(%ebp) = a.c -> al

		compb	%al, 20(%ebp)			# comp a.c con b
		jne 	else

		movl 	$0, %eax
		jmp 	endif

else:
		movl 	16(%ebp), %ecx
		movl 	(%ecx), %eax

endif:
		addl 	12(%ebp), %eax
		movl 	%eax, -4(%ebp)

		movl 	%ebp, %esp
		popl 	%ebp
```

### LlamaSencilla

```c
int LlamaSencilla(S1 x, char y) {
      * (x.m) = SencillaSub(x,x.c);
      return x.k;
}
```

%ebp	0
@ret	+4
x		+8
y		+20
		+21

```assembly
		pushl	%ebp
		movl	%esp, %ebp

		pushb	8(%ebp)		# x.c -> pushB porque es un byte. si falla -> pushl
		pushl	16(%ebp)	# x.m
		pushl	12(%ebp)	# x.k
		pushb	8(%ebp)		# x.c

		call LlamaSencilla

		movl 16(%ebp), %ecx
		movl %eax, (%ecx)

		movl 12(%ebp), %eax		# * (x.m) = SencillaSub(x,x.c);
		ret

		addl	$20, %ebp
		movl 	%ebp, %esp
		popl 	%ebp
```

----

```c
#include "elemento.h"

int BuscarElemento(int *low, int *high, int *mid, S1 X, S1 v[])
{  
  	if (X.k == v[*mid].k)
	{
    	return * mid;	// elemento encontrado
	}
  	else
	{
    	if (*mid < *high)
		{
      		* mid = * high;
      		(* low)++;
    	}
		else
		{
      		* mid = * low;
      		(* high)--;
    	}
	}
  	return -1;            // elemento no encontrado
}
```

%ebp	0
@ret	+4
&low	+8
&high	+12
&mid	+16
X		+20
&v		+32
		+36

```assembly
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
```

## Buscar

```c
int Buscar(S1 v[], S1 X, int N)
{
   int low, high, mid;
   int trobat = -1;

   low = 0;
   mid = low;
   high = N-1;
   while (low <= high)
   {
		trobat = BuscarElemento(&low, &high, &mid, X, v);
		if (trobat >= 0) break;
   }

   return trobat;
}
```

low		-16
high	-12
mid		-8
trobat	-4
%ebp	+0
@ret	+4
&v		+8
X		+12
N		+24
		+28


```assembly
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
```
