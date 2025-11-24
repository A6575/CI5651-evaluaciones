# Tarea 8 - Diseño de Algoritmos I

## Ejecución de los archivos `pregunta2.cpp` y `pregunta3.cpp`

Para compilar y ejecutar los programas de los archivos `pregunta2.cpp` y `pregunta3.cpp`, se utiliza un Makefile.

### Comandos del Makefile

- `make pregunta2`: Compila el archivo `pregunta2.cpp` y genera el ejecutable `pregunta2`.
- `make pregunta3`: Compila el archivo `pregunta3.cpp` y genera el ejecutable `pregunta3`.
- `make run-p2`: Compila el archivo `pregunta2.cpp` y ejecuta el programa `pregunta2` generado.
- `make run-p3`: Compila el archivo `pregunta3.cpp` y ejecuta el programa `pregunta3` generado.
- `make clean-p2`: Elimina los ejecutables generados para `pregunta2`.
- `make clean-p3`: Elimina los ejecutables generados para `pregunta3`.
- `make clean`: Elimina todos los ejecutables generados.

### Entradas esperadas

Ambos programas esperan la entrada por consola (stdin). El formato de la entrada depende de la especificación de cada pregunta:

- Un entero positivo para `pregunta2.cpp`
- Un entero positivo N y N pares de enteros para `pregunta3.cpp`.

### Salidas esperadas

La salida se muestra por consola (stdout). El formato de la salida depende de la lógica implementada en cada archivo.