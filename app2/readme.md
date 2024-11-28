# SISTEMAS OPERATIVOS - PROYECTO 2 - PARTE 2

## Tutorial

Para correr el programa, se deben ejecutar los siguientes comandos:

Para compilar:
```bash
[ruta-repositorio]$ make
```

Para ejecutar:
```bash
[ruta-repositorio]$ ./exec/run -m [MARCOS] -a [ALGORITMO] -f [ARCHIVO]
```

Donde:

* `MARCOS` corresponde a la cantidad de marcos de página disponibles en el sistema
* `ALGORITMO` corresponde al algoritmo de reemplazo de páginas y es una de las siguientes opciones:
	- `CLK`: Algoritmo de LRU reloj simple
	- `FIFO`: Algoritmo LRU
	- `LRU`: Algoritmo LRU
	- `OPT`: Algoritmo optimo
* `ARCHIVO` corresponde a la ruta de un archivo que contiene las referencias a páginas virtuales

## Ejemplo

Si el repositorio fue clonado en la carpeta `/home/usuario/Escritorio` con el nombre `proyectoSO-2`.

```bash
/home/usuario/Escritorio/proyectoSO-2$ make
/home/usuario/Escritorio/proyectoSO-2$ ./exec/run -m 3 -a "LRU" -f "./test/references-1.txt"
```