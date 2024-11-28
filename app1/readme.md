# SISTEMAS OPERATIVOS - PROYECTO 2 - PARTE 1

## Tutorial

Para correr el programa, se deben ejecutar los siguientes comandos:

Para compilar:
```bash
[ruta-repositorio]$ make
```

Para ejecutar:
```bash
[ruta-repositorio]$ ./exec/run -s [TAMAÑO] -t [TIEMPO] -p [PRODUCTORES] -c [CONSUMIDORES]
```

Donde:

* `TAMAÑO`: Correponde al tamaño inicial de la cola
* `TIEMPO`: Corresponde al tiempo máximo de espera de los consumidores
* `PRODUCTORES`: Corresponde a la cantidad de productores
* `CONSUMIDORES`: Corresponde a la cantidad de consumidores

Tras la ejecución, se creará automáticamente un archivo log que contiene un seguimiento del estado de la cola.

## Ejemplo

Si el repositorio fue clonado en la carpeta `/home/usuario/Escritorio` con el nombre `proyectoSO-1`.

```bash
/home/usuario/Escritorio/proyectoSO-1$ make
/home/usuario/Escritorio/proyectoSO-1$ ./exec/run -s 10 -t 1 -p 5 -c 5
```