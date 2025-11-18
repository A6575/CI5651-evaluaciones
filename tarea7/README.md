# Tarea 6 - Diseño de Algoritmos I

## Ejecución de los archivos `pregunta2.cpp`,  `pregunta3.cpp` y `pregunta4.cpp`

Para compilar y ejecutar los programas de los archivos `pregunta2.cpp`,  `pregunta3.cpp` y `pregunta4.cpp`, se utiliza un Makefile.

### Comandos del Makefile

- `make pregunta2`: Compila el archivo `pregunta2.cpp` y genera el ejecutable `pregunta2`.
- `make pregunta3`: Compila el archivo `pregunta3.cpp` y genera el ejecutable `pregunta3`.
- `make pregunta4`: Compila el archivo `pregunta4.cpp` y genera el ejecutable `pregunta4`.
- `make run-p2`: Compila el archivo `pregunta2.cpp` y ejecuta el programa `pregunta2` generado.
- `make run-p3`: Compila el archivo `pregunta3.cpp` y ejecuta el programa `pregunta3` generado.
- `make run-p4`: Compila el archivo `pregunta4.cpp` y ejecuta el programa `pregunta4` generado.
- `make clean-p2`: Elimina los ejecutables generados para `pregunta2`.
- `make clean-p3`: Elimina los ejecutables generados para `pregunta3`.
- `make clean-p4`: Elimina los ejecutables generados para `pregunta4`.
- `make clean`: Eliminta los ejecutables generados para todas las preguntas

### Entradas esperadas

Ninguno de los programas espera la entrada por consola (stdin). El formato de la entrada depende de la especificación de cada pregunta:

- `pregunta2.cpp`: un string
- `pregunta3.cpp`: una vector de Point
- `pregunta4.cpp`: un vector de Point y un valor double (radio)

### Salidas esperadas

La salida se muestra por consola (stdout). El formato de la salida depende de la lógica implementada en cada archivo.