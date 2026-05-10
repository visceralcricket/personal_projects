# StreamFinder - Gestor de Películas

---
## Descripción
**Stream Finder** es un programa desarrollado en C para gestionar y explorar grandes catálogos de películas a partir de archivos CSV.
El sistema permite cargar bases de datos como (`Top1500.csv`) y (`IMDbTop250.csv`), agrupar las películas de forma eficiente y realizar
búsquedas rápidas por género, director, década o una búsqueda avanzada mediante género y década. Además, **StreamFinder** tiene la capacidad
de gestionar una *Watchlist* personal y la funcionalidad de asignar calificaciones a nombre del usuario, contando con 2 archivos CSV de ejemplo
para utilizar en el programa ubicados en la siguiente ruta: `streamFinder/ejemplos`

### Estructura del directorio
* `tarea2.c`: Contiene la lógica principal, menús interactivos y el código fuente de las funcionalidades.
* `tdas/`: Carpeta con las implementaciones de los Tipos de Datos Abstractos
   * `list.c` / `list.h`: TDA Lista enlazada genérica
   * `map.c` / `map.h`: TDA Mapa implementado como hashmap personalizado para eficiencia O(1)
   * `extra.c` / `extra.h`: Utilidades para parseo seguro de archivos CSV y limpieza multiplataforma

## Cómo compilar y ejecutar el programa?
Este programa se ha desarrollado en el lenguaje C y puede ejecutarse fácilmente en cualquier IDE que tenga soporte
para los lenguajes de C/C++ como VsCode, Visual Studio, Codeblocks, etc). Si desea ejecutarlo desde la terminal del
equipo, asegúrese de tener ya instalado un compilador de C como GCC (puede verificarlo con el comando `gcc --version` en el terminal).

### Pasos para compilar y ejecutar el programa
---
1. Descargar y descomprimir el archivo `.zip` en alguna carpeta de su elección.
2. Abrir su IDE o terminal de elección y asegurarse de que el compilador de C está instalado
   (Con GCC por ejemplo: gcc --version).
3. Compilar el código contenido en esta carpeta:
  `gcc streamFinder/tarea2.c streamFinder/tdas/*.c -o stream_finder`
4. Una vez compilado, ejecutar el programa con el comando:
   * `./stream_finder` para Powershell / Linux / MacOS
   * `stream_finder.exe` para CMD (Windows)
5. _Nota para terminales de Windows_
   En caso de ejecutar el programa utilizando el terminal y tener problemas con la codificación de caracteres en español,
   utilice el siguiente comando antes de ejecutar el programa: `[Console]::OutputEncoding = [System.text.Encoding]::UTF8`


# Funcionalidades Principales
1. Cargar películas: Lee el archivo CSV de la ruta indicada y distribuye la información por ID, director, género y década
2. Buscar por género: Muestra todas las películas asociadas a un género en específico
3. Buscar por director: Muestra todas las películas dirigidas por el director indicado
4. Buscar por década: Filtra el catálogo para mostrar todas películas lanzadas en la década de un año de referencia
5. Buscar por género y década: Búsqueda avanzada que combina ambos criterios ya mencionados
6. Gestionar watchlist: Submenú que permite agregar peliculas por ID, eliminarlas o visualizar la lista de películas por ver
7. Calificar película: Permite a un usuario registrar una calificación de 1-10 a una película especifica por su ID
8. Salir: Cierre del programa de forma segura


## Ejemplo de uso paso a paso
1. Opción 1 (Cargar Películas):
   * Se ingresa la ruta del archivo: `streamFinder/Top1500.csv`
   * El sistema confirma la carga exitosa indicando la cantidad de películas leídas.

2. Opción 2 (Buscar por género):
   * Se ingresa el género: Action
   * El programa imprime los detalles, valoraciones y géneros de todas las películas de acción.

3. Opción 6 (Gestionar Watchlist) -> Opción 1 (Agregar película):
   * Se ingresa el ID de una película vista en la búsqueda anterior (ej. tt0110912)
   * El sistema confirma: |-- Película agregada correctamente --|

4. Opción 6 (Gestionar Watchlist) -> Opción 3 (Mostrar lista):
   * Se imprime la película recién agregada a la lista de pendientes.

5. Opción 6 -> Opción 4 (Volver):
   * Retorna al menú principal.

6. Opción 8 (Salir):
   * Se limpia la memoria y cierra el programa.

## Opciones que no funcionan correctamente / puntos a considerar
* Estado actual: Todas las funciones listadas operan de manera óptima. No existen funcionalidades
   incompletas ni errores de compilación.
* Archivos CSV: Se asume que el archivo CSV cargado respeta el formato de `Top1500.csv`, delimitado
   por comas y con campos distribuídos de una forma concreta.
* Manejo de entradas: El programa cuenta con limpieza de buffer personalizada (limpiarBufferEntrada)
   y se implementó una versión modificada (in-house) de un trabajo previo `hashmap.c` para garantizar una experiencia óptima

### Contribuciones
* Felipe: Desarollo de la lógica en el código fuente (tarea2.c), adaptación del TDA Mapa a HashMap y aplicación de programación defensiva.
