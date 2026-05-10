#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ID_SIZE 20
#define MAX_LINEA 16

typedef struct {
  char id[ID_SIZE];
  List *genres;
  char title[256];
  char director[256];
  float rating;
  int year;
  Map *user_ratings;
} Film;

// ============ Prototipos de funciones ============

// --- Utilidades y menús ---
void separador1();
void separador2();
void mostrarMenuPrincipal();
void limpiarBufferEntrada();
char leerOpcionCaracter();

// --- Core y memoria ---
int is_equal_str(void *key1, void *key2);
void insertarEnMapaDeListas(Map *map, char *clave, Film *pelicula);
void cargarPeliculas(Map *pelis_byid, Map *pelis_bydir,
  Map *pelis_bygenres, Map *pelis_bydecade);
void limpiarData(Map *pelis_byid, Map *pelis_bygenres, Map *pelis_bydir,
  Map *pelis_bydecade, List *watchlist);

// --- Búsquedas y visualizaciones ---
void imprimirPelicula(Film *pelicula);
void buscarPorGenero(Map *pelis_bygenres);
void buscarPorDirector(Map *pelis_bydir);
void buscarPorDecada(Map *pelis_bydecade);
void busquedaAvanzada(Map *pelis_bygenres);

// --- Watchlist y Calificaciones ---
void mostrarMenuWatchlist();
void gestionarWatchlist(Map *pelis_byid, List *watchlist);
void agregarALista(Map *pelis_byid, List *watchlist, char *id);
void eliminarDeLista(List *watchlist, char *id);
void calificarPelicula(Map *pelis_byid);

// --- Función main ---

int main() {
  char opcion;
  
  Map *pelis_byid = map_create(is_equal_str);
  Map *pelis_bygenres = map_create(is_equal_str);
  Map *pelis_bydir = map_create(is_equal_str);
  Map *pelis_bydecade = map_create(is_equal_str);
  List *watchlist = list_create();
  

  do {
    mostrarMenuPrincipal();
    printf("\nIngrese su opción\n< ");
    // scanf(" %c", &opcion); <- Utilizar este método no permitía
    // imprimir correctamente los mensajes de "opción no válida".
    opcion = leerOpcionCaracter();

    switch (opcion) {
    case '1':
      cargarPeliculas(pelis_byid, pelis_bydir,
        pelis_bygenres, pelis_bydecade);
      break;
    case '2':
      buscarPorGenero(pelis_bygenres);
      break;
    case '3':
      buscarPorDirector(pelis_bydir);
      break;
    case '4':
      buscarPorDecada(pelis_bydecade);
      break;
    case '5':
      busquedaAvanzada(pelis_bygenres);
      break;
    case '6':
      gestionarWatchlist(pelis_byid, watchlist);
      break;
    case '7':
      calificarPelicula(pelis_byid);
      break;

    case '8':
      break;

    default:
      printf("Opción no válida.\n");
      break;
    }
    
    presioneTeclaParaContinuar();

  } while (opcion != '8');
  
  limpiarPantalla();
  // Liberar memoria
  limpiarData(pelis_byid, pelis_bygenres,
    pelis_bydir, pelis_bydecade, watchlist);
  
  return 0;
}

void separador1() {
  puts("-----------------------------------------");
}

void separador2() {
  puts("=========================================\n");
}

void mostrarMenuPrincipal() {
  limpiarPantalla();
  separador1();
  puts("       |-- StreamFinder 📽️🍿 --|");
  separador2();

  puts("1) Cargar Películas");
  puts("2) Buscar por género");
  puts("3) Buscar por director");
  puts("4) Buscar por década");
  puts("5) Buscar por género y década");
  puts("6) Gestionar Watchlist");
  puts("7) Calificar película");
  puts("8) Salir");
}

/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

void limpiarBufferEntrada() {
  int c;
  while((c=getchar())!='\n' && c != EOF);
}

char leerOpcionCaracter() {
  char linea[MAX_LINEA];
  if(!fgets(linea, sizeof(linea), stdin)) return '\0';
  if(strchr(linea, '\n') == NULL) limpiarBufferEntrada();

  int i=0;
  while(linea[i] && isspace((unsigned char) linea[i])) i++;

  return linea[i] ? linea[i] : '\0';
}

void insertarEnMapaDeListas(Map *map, char *clave, Film *pelicula) {
  if(!map || !clave || !pelicula) return;

  MapPair *pair = map_search(map, clave);
  List *lista;
  if(!pair) {
    lista = list_create();
    char *copiaClave = _mystrdup(clave);
    map_insert(map, copiaClave, lista);
  }
  else lista = pair->value;
  list_pushBack(lista, pelicula);
}

void cargarPeliculas(Map *pelis_byid, Map *pelis_bydir,
  Map *pelis_bygenres, Map *pelis_bydecade) {
  // Limpiar buffer de entrada
  limpiarBufferEntrada();
  
  char ruta[100];
  printf("$ Ingrese la ruta del archivo CSV, ej: stream_finder\\ejemplos\\Top1500.csv\n< ");
  fgets(ruta, 100, stdin);
  ruta[strcspn(ruta, "\n")] = '\0';

  FILE *archivo = fopen(ruta, "r");
  if (!archivo) {
    perror("Error al abrir el archivo");
    return;
  }

  char **campos = leer_linea_csv(archivo, ',');
  int cantidad = 0;

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Datos corrompidos | sin titulo ni ID
    if(campos[1] == NULL || campos[1][0] == '\0' ||
      campos[5]==NULL || campos[5][0]=='\0') continue;
    Film *pelicula = (Film *)malloc(sizeof(Film));
    if(!pelicula) return;

    // Mapeo de columnas según Top1500.csv
    strncpy(pelicula->id, campos[1], ID_SIZE-1);
    pelicula->id[ID_SIZE-1] = '\0';
    
    strncpy(pelicula->title, campos[5], 255);
    pelicula->title[255] = '\0';
    strncpy(pelicula->director, campos[14], 255);
    pelicula->director[255] = '\0';
    
    pelicula->rating = atof(campos[8]);
    pelicula->year = atoi(campos[10]);
    pelicula->user_ratings = map_create(is_equal_str);

    // Duplicar cadena antes de hacer split
    char *genres_aux = _mystrdup(campos[11]);
    pelicula->genres = split_string(genres_aux, ",");
    free(genres_aux);
    
    map_insert(pelis_byid, pelicula->id, pelicula);
    insertarEnMapaDeListas(pelis_bydir, pelicula->director, pelicula);

    char *tmpGenero = list_first(pelicula->genres);
    while(tmpGenero) {
      if(tmpGenero[0]==' ') tmpGenero++;
      insertarEnMapaDeListas(pelis_bygenres, tmpGenero, pelicula);
      tmpGenero = list_next(pelicula->genres);
    }
    char decada[10];
    sprintf(decada, "%d", (pelicula->year/10)*10);
    insertarEnMapaDeListas(pelis_bydecade, decada, pelicula);
    
    cantidad++;
  }
  fclose(archivo);
  printf("|-- Se cargaron %d películas correctamente ✅ --|\n", cantidad);

  limpiarBufferEntrada();
}

void imprimirPelicula(Film *pelicula) {
  if(!pelicula) {
    separador1();
    printf("No hay películas para mostrar.\n");
    separador2();
    return;
  }
  separador1();
  printf("📽️: [%s] %s\n", pelicula->id, pelicula->title);
  printf("| Director: %-20s | Año: %d | Rating: %.1f\n", pelicula->director,
    pelicula->year, pelicula->rating);

  if(pelicula->user_ratings) {
    printf("\n|-- Calificaciones de usuarios --|\n");
    MapPair *rating = map_first(pelicula->user_ratings);
    while(rating) {
      printf("| %s : %d\n", (char *)rating->key, *((int *) rating->value));
      rating = map_next(pelicula->user_ratings);
    }
  }
  printf("\n|-- Géneros --|\n");
  char *g = list_first(pelicula->genres);
  char *gNext;
  while(g!=NULL) {
    gNext = list_next(pelicula->genres);
    printf("%s%s", g, (gNext) ? ", " : "\n");
    g=gNext;
  }
  separador2();
}

void buscarPorGenero(Map *pelis_bygenres) {
  limpiarBufferEntrada();
  
  char genero[50];
  printf("$ Ingrese el género de la película\n< ");
  fgets(genero, 50, stdin);
  genero[strcspn(genero, "\n")] = '\0';

  MapPair *pair = map_search(pelis_bygenres, genero);
  if(!pair) {
    separador1();
    printf("|-- No se encontraron películas para el género %s solicitado --|\n", genero);
    separador2();
    return;
  }
  List* lista = pair->value;
  Film *pelicula = list_first(lista);
  separador1();
  printf("\n|-- Películas del género --| %s\n< \n", genero);
  for(; pelicula!=NULL; pelicula=list_next(lista)) imprimirPelicula(pelicula);
  separador2();
  
  limpiarBufferEntrada();
}

void buscarPorDirector(Map *pelis_bydir) {
  limpiarBufferEntrada();
  
  char tmpDirector[50];
  printf("$ Ingrese nombre del director\n< ");
  fgets(tmpDirector, 50, stdin);
  tmpDirector[strcspn(tmpDirector, "\n")] = '\0';

  MapPair *pair = map_search(pelis_bydir, tmpDirector);
  if(!pair) {
    separador1();
    printf("|-- No se encontraron películas del director %s --|\n", tmpDirector);
    separador2();
    return;
  }
  List *lista = pair->value;
  Film *pelicula = list_first(lista);
  for(; pelicula!=NULL; pelicula=list_next(lista)) imprimirPelicula(pelicula);

  limpiarBufferEntrada();
}

void buscarPorDecada(Map *pelis_bydecade) {
  limpiarBufferEntrada();
  
  int tmpYear;
  printf("$ Ingrese año de referencia para la búsqueda\n< ");
  fscanf(stdin, "%d", &tmpYear);

  char decadaCadena[10];
  sprintf(decadaCadena, "%d", (tmpYear/10)*10);
  
  MapPair *pair = map_search(pelis_bydecade, decadaCadena);
  if(!pair) {
    separador1();
    printf("|-- No se encontraron películas registradas en la década de %s --|\n", decadaCadena);
    separador2();
    return;
  }
  List *lista = pair->value;
  Film *pelicula = list_first(lista);
  for(; pelicula!=NULL; pelicula=list_next(lista)) imprimirPelicula(pelicula);

  limpiarBufferEntrada();
}

void busquedaAvanzada(Map *pelis_bygenres) {
  limpiarBufferEntrada();
  
  char tmpGenero[50];
  int tmpYear;
  printf("$ Ingrese el género a buscar\n< ");
  fgets(tmpGenero, 50, stdin);
  tmpGenero[strcspn(tmpGenero, "\n")] = '\0';

  printf("\n$ Ingrese el año de referencia\n< ");
  fscanf(stdin, "%d", &tmpYear);
  while(getchar()!='\n');

  int decadaBuscada = (tmpYear/10)*10;
  MapPair *pair = map_search(pelis_bygenres, tmpGenero);

  if(!pair) {
    printf("|-- El género indicado no existe en la base de datos --|\n");
    return;
  }

  List *lista = pair->value;
  int encontrados = 0;
  Film *pelicula = list_first(lista);
  for(; pelicula!=NULL; pelicula=list_next(lista)) {
    if((pelicula->year /10)*10 == decadaBuscada) {
      imprimirPelicula(pelicula);
      encontrados++;
    }
  }
  if(!encontrados) {
    printf("|-- No se encontraron coincidencias para ambos criterios --|\n");
    limpiarBufferEntrada();
    return;
  }
  limpiarBufferEntrada();
}

void mostrarMenuWatchlist() {
  limpiarPantalla();
  separador1();
  puts("|-- Gestión de Watchlist --|\n");
  separador2();

  puts("1) Agregar película por ID");
  puts("2) Eliminar película por ID");
  puts("3) Mostrar lista de películas");
  puts("4) Volver");
}

void agregarALista(Map *pelis_byid, List *watchlist, char *id) {
  MapPair *pair = map_search(pelis_byid, id);
  if(!pair) {
    printf("\n|-- ID no encontrado --|\n");
    return;
  }
  Film *pelicula = pair->value;
  Film *tmp = list_first(watchlist);
  while(tmp!=NULL) {
    if(strcmp(tmp->id, pelicula->id)==0) {
      printf("|-- Película ya agregada en la watchlist! --|\n");
      return;
    }
    tmp = list_next(watchlist);
  }
  list_pushBack(watchlist, pelicula);
  printf("|-- Película agregada correctamente --|\n");
}

void eliminarDeLista(List *watchlist, char *id) {
  Film *pelicula = list_first(watchlist);
  int encontrado = 0;
  while(pelicula!=NULL) {
    if(strcmp(pelicula->id, id)==0) {
      list_popCurrent(watchlist);
      encontrado = 1;
      break;
    }
    pelicula = list_next(watchlist);
  }
  if(encontrado) printf("|-- Pelicula con ID [%s] eliminada con éxito --|\n", id);
  else printf("|-- El ID [%s] no se encontró en la Watchlist --|\n", id);
}

void gestionarWatchlist(Map *pelis_byid, List *watchlist) {
  char opcion;
  char tmpID[ID_SIZE];
  do {
    mostrarMenuWatchlist();
    limpiarBufferEntrada();
    
    printf("Ingrese su opción\n< ");
    // fscanf(stdin, " %c", &opcion); <- Mismo caso que en el menú principal,
    // este método provoca que los mensajes de "opción no válida" desaparezcan instantáneamente.
    opcion = leerOpcionCaracter();

    if(opcion=='4') break;
    
    switch(opcion) {
      case '1':
        printf("$ Ingrese el ID de la película\n< ");
        fgets(tmpID, 20, stdin);
        tmpID[strcspn(tmpID, "\n")] = '\0';
        agregarALista(pelis_byid, watchlist, tmpID);
        break;
      
      case '2':
        printf("$ Ingrese el ID de la película\n< ");
        fgets(tmpID, 20, stdin);
        tmpID[strcspn(tmpID, "\n")] = '\0';
        eliminarDeLista(watchlist, tmpID);
        break;
          
      case '3': {
        Film *tmpPelicula = list_first(watchlist);
        for(; tmpPelicula!=NULL; tmpPelicula=list_next(watchlist)) imprimirPelicula(tmpPelicula);
        break;
      }

      default:
          printf("Opción no válida.\n");
          break;
    }
    presioneTeclaParaContinuar();
  } while(opcion!='4');
}

/* +++
Esta función existe para hacer limpieza de los mapas utilizados y el contenido
que estas almacenan luego de reservar memoria para no tener memory leaks. Se define
multimapas para así no tener que separar el proceso de limpieza de la memoria almacenada
por cada mapa creado por criterio, de esta forma en un único ciclo se libera la data de
todos los mapas en su conjunto. Es vital liberar esta variable multimapas
antes que el mapa_byid's porque de lo contrario los punteros dentro de cada estructura
en multimapas apuntará a basura (colgantes) y tendrán comportamiendo indefinido.

====== Explicación de cómo funciona ======
+ Limpieza de mapas agrupados (multimapas): se liberan las claves, se limpian las listas (list_clean)
  asociadas, se liberan los punteros a las listas y se limpia cada mapa en sí (map_clean).

+ Limpieza del mapa principal por ID; Se libera cada género en la lista, se limpia la lista de géneros,
  se libera el mapa de calificaciones de usuarios (claves y valores), se limpia el mapa de calificaciones
  y se libera el dato pelicula de tipo Film.

+ Limpieza de la watchlist: Se limpia la lista y luego se libera el puntero watchlist en sí.

Para indicar el cierre adecuado del programa se imprime un mensaje final el cual además fue utilizado
para hacer debugging en casos de core dump a lo largo del desarrollo del programa.
--- */

void limpiarData(Map *pelis_byid, Map *pelis_bygenres,
  Map *pelis_bydir, Map *pelis_bydecade, List *watchlist) {
  
  // Limpieza de los mapas agrupados por criterio
  Map *multimapas[] = {pelis_bygenres, pelis_bydir, pelis_bydecade};
  for(int i=0; i<3; i++) {
    if(!multimapas[i]) continue; // Si el mapa está vacío, se ignora
    MapPair *pair = map_first(multimapas[i]);
    // Iterar y limpiar mientras exista un dato
    while(pair) { 
      free(pair->key);
      if(pair->value) { // Evitar acceder a un dato nulo
        list_clean((List *) pair->value);
        free(pair->value);
      }
      pair = map_next(multimapas[i]);
    }
    map_clean(multimapas[i]);
  }
  // Verificar si existe mapa de pelis por id
  if(pelis_byid) {
    MapPair *pair = map_first(pelis_byid);
    while(pair) {
      Film *pelicula = (Film *) pair->value;

      if(pelicula) {
        // Liberar memoria del mapa por género si existe
        if(pelicula->genres) {
          char *g = list_first(pelicula->genres);
          while(g) { // Liberar lista de géneros
            free(g);
            g = list_next(pelicula->genres);
          }
          list_clean(pelicula->genres);
          free(pelicula->genres);
        }
        // Liberar memoria de las calificaciones de usuarios si es que hay
        if(pelicula->user_ratings) {
          MapPair *rating = map_first(pelicula->user_ratings);
          while(rating) {
            free(rating->key);
            free(rating->value);
            rating = map_next(pelicula->user_ratings);
          }
          map_clean(pelicula->user_ratings);
        }
        free(pelicula);
      }
      pair = map_next(pelis_byid);
    }
    map_clean(pelis_byid);
  }

  if(watchlist) {
    list_clean(watchlist);  
  }
  free(watchlist);
  printf("Cerrando programa.. gracias por su paciencia.\n");
}
 
void calificarPelicula(Map *pelis_byid) {
  limpiarBufferEntrada();
  
  char tmpID[ID_SIZE];
  char user[50];
  int *nota = malloc(sizeof(int));
  if(!nota) return;

  printf("$ Ingrese id de la película\n< ");
  fgets(tmpID, 50, stdin);
  tmpID[strcspn(tmpID, "\n")] = '\0';

  MapPair *pair = map_search(pelis_byid, tmpID);
  if(!pair) {
    printf("|-- Película no encontrada --|\n");
    free(nota);
    return;
  }

  Film *pelicula = pair->value;
  printf("$ Ingrese su nombre de usuario\n< ");
  fgets(user, 50, stdin);
  user[strcspn(user, "\n")] = '\0';
  printf("\n$ Ingrese calificación (1-10)\n< ");
  fscanf(stdin, "%d", nota);
  while(getchar()!='\n');

  if((*nota) < 1 || (*nota) > 10) {
    printf("Nota no válida.\n");
    free(nota);
    return;
  }

  MapPair *existente = map_search(pelicula->user_ratings, user);
  if(existente) {
    free(existente->value);
    existente->value = nota;
  }
  else map_insert(pelicula->user_ratings, _mystrdup(user), nota);

  printf("|-- Calificación para la película %s registrada con éxito --|\n", pelicula->title);
}
