# Tarea 6 - Diseño de Algoritmos I

## Ejecución de los archivos `pregunta1.cpp`,  `pregunta2.cpp` y `pregunta3.cpp`

Para compilar y ejecutar los programas de los archivos `pregunta1.cpp`,  `pregunta2.cpp` y `pregunta3.cpp`, se utiliza un Makefile.

### Comandos del Makefile

- `make pregunta1`: Compila el archivo `pregunta1.cpp` y genera el ejecutable `pregunta1`.
- `make pregunta2`: Compila el archivo `pregunta2.cpp` y genera el ejecutable `pregunta2`.
- `make pregunta3`: Compila el archivo `pregunta3.cpp` y genera el ejecutable `pregunta3`.
- `make run-p1`: Compila el archivo `pregunta1.cpp` y ejecuta el programa `pregunta1` generado.
- `make run-p2`: Compila el archivo `pregunta2.cpp` y ejecuta el programa `pregunta2` generado.
- `make run-p3`: Compila el archivo `pregunta3.cpp` y ejecuta el programa `pregunta3` generado.
- `make clean-p1`: Elimina los ejecutables generados para `pregunta1`.
- `make clean-p2`: Elimina los ejecutables generados para `pregunta2`.
- `make clean-p3`: Elimina los ejecutables generados para `pregunta3`.

### Entradas esperadas

Todos los programas esperan entrada por consola (stdin). El formato de la entrada depende de la especificación de cada pregunta:

- `pregunta1.cpp`: arreglo de N elementos, seguido de Q operaciones `multiswap`
- `pregunta2.cpp`: arbol de N nodos y N-1 aristas, cada una con su respectivo predicado. Luego, recibe Q operaciones `forall/exists/toggle`
- `pregunta3.cpp`: arreglo de N elementos, seguido de Q consultas `consultar`
### Salidas esperadas

La salida se muestra por consola (stdout). El formato de la salida depende de la lógica implementada en cada archivo.