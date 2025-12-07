# Tarea 9 - Diseño de Algoritmos I

## Sobre el archivo python/miller-rabin.py

El archivo `python/miller-rabin.py` contiene una implementación del test de primalidad de Miller-Rabin. Este incluye funciones para generar números aleatorios dentro de un rango, realizar la prueba para una base específica, y ejecutar múltiples iteraciones del test para aumentar la confianza en el resultado.

Este archivo se utiliza para resolver la Pregunta 1 de la tarea, que consiste en determinar si `181093918109391810939` es primo o compuesto utilizando el test de Miller-Rabin.

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

Ninguno de los programas espera la entrada por consola (stdin). El formato de la entrada depende de la especificación de cada pregunta:

- `pregunta2.cpp`: dos matrices cuadradas A y B de tamaño n x n, y un decimal epsilon.
- `pregunta3.cpp`: una lista de aristas que representan un grafo no dirigido.
 
### Salidas esperadas

La salida se muestra por consola (stdout). El formato de la salida depende de la lógica implementada en cada archivo.