#ifndef INT_RANDOMIZER_H
#define INT_RANDOMIZER_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

// Macros para crear directorios correctamente dependiendo del OS
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0777)
#endif

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

// Función para limpiar la pantalla
void limpiarPantalla() { system(CLEAR_COMMAND); }


#endif