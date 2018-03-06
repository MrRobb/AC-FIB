## Lenguaje máquina (x86)

### Historia

#### IBM - i8086

IBM se hizo con el mercado con el procesador de **16 bits** llamado i8086.

Era de números enteros, **no podías hacer operaciones aritméticas con decimales** (solo podías simularlas).

Hizo un **chip aritmético** para aumentar la velocidad de computación.

#### IBM - i80286

Aumenta el espacio de direcciones a **24 bits**.

#### IBM - i80386 (el de las prácticas)

Se extiende a **32 bits**. Todos **los registros sirven para todo**.

> Recordad que en las prácticas hay que poner la opción -m32 para compilar con 32 bits.

#### Intel - Pentium MMX (1997)

Intel hizo un conjunto de instrucciones **(instrucciones multimedia)** para procesamiento vectorial de datos. Es decir, con una sola operación se podían modificar vectores.

#### AMD (2003)

Extiende a **64 bits**.

### Instrucciones

Lenguaje máquina x86 que usaremos es CISC.

Por lo tanto hay diferencias:

<p align="center">
	<img src="../images/24.png" width=100%>
</p>

<p align="center">
	<img src="../images/22.png" width=100%>
</p>

#### Tipos de datos

- Enteros
- Reales (con coma flotante)

Cada tipo de dato tiene un rango de número que caben dentro (ambos incluidos):
- Naturales:
	- byte: 0 .. 255
	- word: 0 .. 65.535
	- long: 0 .. 4.294.967.215
- Enteros:
	- byte: -128 .. 127
	- word: -32.768 .. 32.767
	- long: -2.147.483.648 .. 2.147.483.647
- Reales:
	- byte (32 bits): 1,18\*10^-38 .. 3,40\*10^38
	- word (64 bits): 2,23\*10^-308 .. 1,79\*10^308
	- long (80 bits): 3,37\*10^-4932 .. 1,18\*10^-4932

> MOV[ B (8 bits)| L (32 bits)|W (16 bits) ]

No hay structs, ni matrices, ni ningún tipo estructurado

#### Registros

<p align="center">
	<img src="../images/23.png" width=100%>
</p>

// TO-DO: revisar (arriba)

##### Son registros little endian

<p align="center">
	<img src="../images/25.png" width=40%>
	<img src="../images/26.png" width=40%>
</p>

#### Ejemplos de instrucciones

```assembly
// Inmediatos
$19
$-3
$0x2A
$0x2A45

// Registros
%eax
%ah
%esi

// Memoria:  D(Rb, Ri, s) -> M[Rb + Ri * s + D]
a(b,c,d) = a + b + c * d
```

<p align="center">
	<img src="../images/27.png" width=80%>
</p>

<p align="center">
	<img src="../images/28.png" width=50%>
</p>

#### Codificación de memoria

(es bastante jodido)

// TO-DO: explicarlo

<p align="center">
	<img src="../images/29.png" width=80%>
</p>

### INSTRUCCIONES DE MOVIMIENTO

<p align="center">
	<img src="../images/30.png" width=100%>
</p>

> En el manual de Microsoft va al revés (MOVx op2, op1)

**MOVSxy** --> Extiende el signo.

**MOVZxy** --> Pone ceros.

> Si se te olvida la -m32 el push y el pop se vuelven locos.

**LEAL** --> Mueve la dirección al registro de destino.

> En todos se puede mover de op1 a op1

### INSTRUCCIONES ARITMÉTICAS

<p align="center">
	<img src="../images/31.png" width=100%>
</p>

<p align="center">
	<img src="../images/32.png" width=100%>
</p>

**IMULL** --> Sé que el resultado puede tener más de 32 bits.

**IMUL** --> Sé que el resultado no tiene más de 32 bits.

**MULL** --> Multiplica el %eax por el op1 que puede tener 64 bits.

**CLTD** --> Convierte 32 bits (%eax) en 64 bits (%edx %eax).

**IDIVL** --> Divide enteros.

**DIVL** --> Divide naturales.

### INSTRUCCIONES LÓGICAS

<p align="center">
	<img src="../images/33.png" width=100%>
</p>

### INSTRUCCIONES DE SALTO

<p align="center">
	<img src="../images/34.png" width=100%>
</p>

### FLAGS DE CONDICIONES

<p align="center">
	<img src="../images/35.png" width=100%>
</p>

### Ejemplos

<p align="center">
	<img src="../images/36.png" width=100%>
</p>

```assembly
.data				# el código empieza aquí
	.align 4 		# empieza en una dirección múltiple de 4
	.string "Esto es un string.\n"
.text
	.align 4 		# empieza en una dirección múltiple de 4
	.globl main		# hace que empiece haciendo el main
	.type main, @function

main:	...
		...
```

### Traducción C --> Assembly

> El profesor se ha saltado los ifs, whiles, etc: "Ya lo habéis hecho en IC/EC."

> Los punteros son de 4 bytes. Ya que nuestra máquina es de 32 bits.

|TIPO|sizeof(TIPO)|
|----|------------|
|	char	|	1 byte	|
|	char*	|	4 bytes	|
|	int	|	4 bytes	|
|	int*	|	4 bytes	|
|	double	|	8 bytes	|

#### Vectores

int V[8];

**V[i]** --> **@V + (i) *  sizeof(int)**

```cpp
int Vi(int V[100], int i) {
	return V[i];
}
```

<p align="center">
	<img src="../images/37.png" width=70%>
</p>

#### Matrices

int mat[10][10];

**mat[i][j]** --> **@mat + (Ncolumnas * i + j) * sizeof(int)**

```cpp
int mfc(int mat[50][80], int fil, int col) {
	return mat[fil][col];
}
```

<p align="center">
	<img src="../images/38.png" width=70%>
</p>
