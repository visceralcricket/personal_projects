#include <stdio.h>
#include <stdlib.h>

#define NULO -1

typedef struct { // Tipo de dato tipoVuelo
  
  size_t codigoVuelo;
  size_t destino;
  size_t prioridad;
  float tiempoAbordaje;
  
} tipoVuelo;

typedef struct {
  
  float maximoTiempoAbordaje;
  size_t cantVuelosRepetidos;
  
} duplaValoresEstadist;

void poblarOrd(tipoVuelo *vector, size_t cantVuelos, size_t *talla, duplaValoresEstadist *vectorCoeficientes); // Función poblar el vector de tipoVuelo's
void mostrar(const tipoVuelo *vector, const size_t talla, const char *titulo);
int cmp(const void *pivote, const void *elemento);
size_t buscarCodigo(tipoVuelo *vector, size_t talla, size_t codigo); // Verificar si el código de vuelo está repetido

int main() {
    
    // Variables-> Cantidad de datos a procesar, talla final/real de la estructura formada
    size_t cantVuelos, talla = 0;
    duplaValoresEstadist vectorCoeficientes = {0.0, 0};

    scanf("%zu", &cantVuelos);
    
    tipoVuelo vector[cantVuelos];
    
    poblarOrd(vector, cantVuelos, &talla, &vectorCoeficientes);
    
    printf("Se registraron %zu vuelos, se procesarán %zu.\n", cantVuelos, talla);
    mostrar(vector, talla, "LISTADO ORIGINAL DE ENTREGAS ESTELARES");
    
    qsort(vector, talla, sizeof(tipoVuelo), cmp);
    mostrar(vector, talla, "LISTADO DE EJECUCIÓN DE ENTREGAS      ");
    
    printf("\n\t     ==== Mayor tiempo de abordaje: %.2f ====", vectorCoeficientes.maximoTiempoAbordaje);
    printf("\n\t==== Cantidad de códigos de vuelo repetidos: %zu ====", vectorCoeficientes.cantVuelosRepetidos);
    
    return 0;
}


int cmp(const void *pivote, const void *elemento) {
  
    const tipoVuelo *ptrPivote = (const tipoVuelo *) (pivote);
    const tipoVuelo *ptrElemento = (const tipoVuelo *) (elemento);

    // Condición A-> Ordenar de acuerdo a la prioridad de los registros
    if (ptrPivote->prioridad > ptrElemento->prioridad) return -1;
    if (ptrPivote->prioridad < ptrElemento->prioridad) return 1;

    // Sí los registros son iguales, es decir, no cumplen ningún caso de condicion A, el programa opta por la condición B:
    // Condición B-> Ordenar de acuerdo al tiempo de abordaje
    if (ptrPivote->tiempoAbordaje < ptrElemento->tiempoAbordaje) return -1;
    if (ptrPivote->tiempoAbordaje > ptrElemento->tiempoAbordaje) return 1;

    // En caso de que los registros sean iguales en -ambas- condiciones, A y B, determinamos que es suficiente información para evaluar y omitimos el ordenamiento
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

void poblarOrd(tipoVuelo *vector, size_t cantVuelos, size_t *talla, duplaValoresEstadist *vectorCoeficientes) {
  
  float mayorTiempo = 0.0;
  size_t repetidos = 0;
  tipoVuelo registro; // Crear el registro que se va a leer por cada ciclo-> se irá reseteando
  
  for(size_t i=0; i<cantVuelos; i++) {
    
    scanf("%zu %zu %zu %f", &registro.codigoVuelo,
    &registro.destino,
    &registro.prioridad,
    &registro.tiempoAbordaje); // Lectura
    
    if(*talla == 0) { // Comprobar si es el primer dato para así no malgastar tiempo verificando si su código está repetido
    
      vector[*talla] = registro;
      (*talla)++; // Aumentar talla/tamaño real
    }
    
      
    size_t posicionCodigo = buscarCodigo(vector, *talla, registro.codigoVuelo); // Verificar que el código de vuelo no se repite
      
    if(posicionCodigo==NULO) { // Caso-> si el código no está presente en el registro, se añade, de lo contrario-> se omite/continúa el ciclo
        
      vector[*talla] = registro;
      (*talla)++;
        
    }
    
    else repetidos++;
    
    if(registro.tiempoAbordaje > mayorTiempo) {
      
      mayorTiempo = registro.tiempoAbordaje;
    }
  }
  
  vectorCoeficientes->maximoTiempoAbordaje = mayorTiempo;
  vectorCoeficientes->cantVuelosRepetidos = repetidos;
}
