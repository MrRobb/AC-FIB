### Bancos

<p align="center">
	<img src="../images/107.png" width=80%>
</p>

> Todas las RAMs se organizan en bancos.

- Para poder acceder a diversos bancos concurrentemente.
- Para ocultar la precarga
- Para ocultar el refresco
- Para que vaya más rápido y que consuma menos (ya que son más peques)

### @Memoria

> En este caso:

- 15 bits de fila
- 10 bits de columna
	- 8 bits de columna
	- 2 bits para seleccionar el byte en la columna
- 3 bits de banco

### Cronogramas

<p align="center">
	<img src="../images/108.png" width=80%>
</p>

<p align="center">
	<img src="../images/109.png" width=80%>
</p>

##### Donde está la dirección 0x1DF038A6B

|   1|1101|1111|0000|0011|1000|1010|0110|1011
|----|----|----|----|----|----|----|----|----|----|----|
|canal|3..1 -> DIM  |  fila  |  fila  | fila   | 3..2 -> fila |  columna  | columna  |  3 -> columna  |
|    | 0 -> fila  |    |    |    | 1..0 -> columna |    |   |  2..0 -> Chip  |

> Conclusión: hay muchas maneras de organizarlo

<p align="center">
	<img src="../images/110.png" width=80%>
</p>

Pero unas son más eficientes que otras.

Me interesa cambiar cada poco tiempo de banco para hacer accesos concurrentes.

> Por lo tanto. Esto:

<p align="center">
	<img src="../images/111.png" width=80%>
</p>

> Es mejor que esto:

<p align="center">
	<img src="../images/112.png" width=80%>
</p>

### Accederiamos así

<p align="center">
	<img src="../images/113.png" width=80%>
</p>

<p align="center">
	<img src="../images/114.png" width=80%>
</p>

> Recomendación: lee las transparencias con calma (no solo las de este resumen, todas las de este tema)

> Mirarse corrección y detección de errores (transparencias)
