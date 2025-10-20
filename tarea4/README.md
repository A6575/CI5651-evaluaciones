# Tarea 4 - Diseño de Algoritmos I

## Ejecución de los archivos `pregunta2.cpp`, `pregunta3.cpp` y `pregunta4.cpp`

Para compilar y ejecutar los programas de los archivos `pregunta2.cpp`, `pregunta3.cpp` y `pregunta4.cpp`, se utiliza un Makefile.

### Comandos del Makefile

- `make pregunta2`: Compila el archivo `pregunta2.cpp` y genera el ejecutable `pregunta2`.
- `make pregunta3`: Compila el archivo `pregunta3.cpp` y genera el ejecutable `pregunta3`.
- `make pregunta4`: Compila el archivo `pregunta4.cpp` y genera el ejecutable `pregunta4`.
- `make run-p2`: Compila el archivo `pregunta2.cpp` y ejecuta el programa `pregunta2` generado.
- `make run-p3 arg=<argumento>`: Compila el archivo `pregunta3.cpp` y ejecuta el programa `pregunta3` generado.
  `<argumento>` debe ser reemplazado por el tamaño del arreglo.
- `make run-p4`: Compila el archivo `pregunta4.cpp` y ejecuta el programa `pregunta4` generado.
- `make clean-p2`: Elimina los ejecutables generados para `pregunta2`.
- `make clean-p3`: Elimina los ejecutables generados para `pregunta3`.
- `make clean-p4`: Elimina los ejecutables generados para `pregunta4`.

### Entradas esperadas

Solo los programas `pregunta3.cpp` y `pregunta4.cpp` esperan la entrada por consola (stdin). El formato de la entrada depende de la especificación de cada pregunta:

- Un entero `n` (numero de maletas) seguido de `n` pares de enteros (coordenadas de las maletas) para `pregunta4.cpp`.
- Comandos de asignación, consulta, limpieza del arreglo para `pregunta3.cpp`. El programa indica el formato esperado al inicio de la ejecución.

### Salidas esperadas

La salida se muestra por consola (stdout). El formato de la salida depende de la lógica implementada en cada archivo.