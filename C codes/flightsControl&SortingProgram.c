#include <stdio.h>
#include <stdlib.h>

#define NULO -1

typedef struct { // Tipo de dato tipoVuelo
  
  size_t codigoVuelo;
  size_t destino;
  size_t prioridad;
  float tiempoAbordaje;
  
} tipoVuelo;

void poblarOrd(tipoVuelo *vector, size_t cantVuelos, size_t *talla); // Función poblar el vector de tipoVuelo's
void mostrar(const tipoVuelo *vector, const size_t talla, const char *titulo);
int cmp(const void *pivote, const void *elemento);
size_t buscarCodigo(tipoVuelo *vector, size_t talla, size_t codigo); // Verificar si el código de vuelo está repetido

int main() {
    
    // Variables-> Cantidad de datos a procesar, talla final/real de la estructura formada
    size_t cantVuelos, talla = 0;
    scanf("%zu", &cantVuelos);
    
    tipoVuelo vector[cantVuelos];
    
    poblarOrd(vector, cantVuelos, &talla);
    
    printf("Se registraron %zu vuelos, se procesarán %zu.\n", cantVuelos, talla);
    mostrar(vector, talla, "LISTADO ORIGINAL DE ENTREGAS ESTELARES");
    
    qsort(vector, talla, sizeof(tipoVuelo), cmp);
    mostrar(vector, talla, "LISTADO DE EJECUCIÓN DE ENTREGAS      ");
    
    return 0;
}


int cmp(const void *pivote, const void *elemento) {
    const tipoVuelo *ptrPivote = (const tipoVuelo *) (pivote);
    const tipoVuelo *ptrElemento = (const tipoVuelo *) (elemento);

    if (ptrPivote->prioridad > ptrElemento->prioridad) return -1;
    if (ptrPivote->prioridad < ptrElemento->prioridad) return 1;

    if (ptrPivote->tiempoAbordaje < ptrElemento->tiempoAbordaje) return -1;
    if (ptrPivote->tiempoAbordaje > ptrElemento->tiempoAbordaje) return 1;

    return 0;
}



size_t buscarCodigo(tipoVuelo *vector, size_t talla, size_t codigo) {
  
  for(size_t i=0; i<talla; i++) {
    
    if(vector[i].codigoVuelo == codigo) return i;
    
  }
  
  return NULO;
}

void mostrar(const tipoVuelo *vector, const size_t talla, const char *titulo) {
  
  printf(" -------------------------------------------------------- \n");
  printf("|         %s         |\n", titulo);
  printf(" -------------------------------------------------------- \n");
  printf("|  CODIGO  |  DESTINO  |  PRIORIDAD  |  TIEMPO (h)       |\n");
  
  for(size_t i=0; i<talla; i++) {
    
    printf("|%9zu |%9zu  |%11zu  |%9.2f          |\n", ((vector+i)->codigoVuelo), ((vector+i)->destino), ((vector+i)->prioridad), ((vector+i)->tiempoAbordaje));
    
  }
  
  printf(" -------------------------------------------------------- \n\n");
}

void poblarOrd(tipoVuelo *vector, size_t cantVuelos, size_t *talla) {
  
  tipoVuelo registro; // Crear el registro que se va a leer por cada ciclo-> se irá reseteando
  
  for(size_t i=0; i<cantVuelos; i++) {
    
    scanf("%zu %zu %zu %f", &registro.codigoVuelo, &registro.destino, &registro.prioridad, &registro.tiempoAbordaje); // Lectura
    
    if(*talla == 0) { // Comprobar si es el primer dato para así no malgastar tiempo verificando si su código está repetido
      vector[*talla] = registro;
      (*talla)++; // Aumentar talla/tamaño real
    }
    
    else {
      
      size_t posicionCodigo = buscarCodigo(vector, *talla, registro.codigoVuelo); // Verificar que el código de vuelo no se repite
      
      if(posicionCodigo==NULO) { // Caso-> si el código no está presente en el registro, se añade, de lo contrario-> se omite/continúa el ciclo
        
        vector[*talla] = registro;
        (*talla)++;
      }
      
    }
    
  }
  
}
