/*
INGRESAR EDADES EN ORDEN


El departamento de estadísticas e información del ministerio de salud, se encuentra realizando un estudio sobre las edades de las personas
contagiadas con COVID 19 durante el primer trimestre del 2022. Los funcionarios de éste departamento, desean registrar las edades
de todas las personas contagiadas en orden creciente, para luego determinar rápidamente cual es la menor y la mayor edad.

Escriba un programa modular en C con funciones propias o predefinidas que realicen las siguientes tareas:

Leer un valor entero positivo que corresponde a la cantidad de personas contagiadas que serán procesadas (función leerCantidad).
Considere que se ingresarán como máximo 1000 edades.
Leer las edades de cada una de las personas contagiadas, insertándolas en un vector ORDENADAS de menor
a mayor (función poblarVectorOrdenado).
show por pantalla el contenido del vector en el formato solicitado (función showVector).
Imprimir por pantalla la menor edad (función printf). 
Imprimir por pantalla la mayor edad (función printf).

Input	Result
5
5 6 7 3 4

Vector Edades Ordenado = [3, 4, 5, 6, 7]
Menor edad = 3
Mayor edad = 7
*/

#include <stdio.h>

#define MAX 100

void show(int *vector, int size, const char *titulo);
void insertarOrdenado(int *vector, int size);
void insert(int *vector, int *realSize, int age, int position);
int searchPosition(int *vector, int realSize, int age);

int main() {
  
  int vector[MAX];
  int size;
  
  scanf("%d", &size);
  
  insertarOrdenado(vector, size);
  show(vector, size, "Vector Edades Ordenado = ");
  
  return 0;
  
}

void show(int *vector, int size, const char *titulo) {
  
  printf("%s", titulo);

  if (size == 0) {
      printf("[\n");
      return;
  }

  printf("[%d", *(vector));
    
  for(unsigned char i = 1; i < size; i++) {
      printf(", %d", *(vector + i));
  }
    
  printf("]\n");
    
  unsigned short menor = vector[0];
  unsigned short mayor = vector[size-1];
    
  printf("Menor edad = %d\n", menor);
  printf("Mayor edad = %d", mayor);
  
}

void insert(int *vector, int *realSize, int age, int position) {
  
  int i = *realSize;
  
  while(i>position) {
    
    *(vector+i) = *(vector+i-1);
    i--;
  }
  
  *(vector+position) = age;
  (*realSize)++;
  
}

int searchPosition(int *vector, int realSize, int age) {
  
  int i = 0;
  
  while(i<realSize && *(vector+i)<age) {
    i++;
  }
  
  return i;
}

void insertarOrdenado(int *vector, int size) {
  
  int age;
  int realSize = 0;
  
  for(int i=0; i<size; i++) {
    
    scanf("%d", &age);
    
    if(realSize == 0) {
      
      *vector = age;
      realSize++;
    }
    
    else {
      
      int position = searchPosition(vector, realSize, age);
      
      if(position == realSize) {
        
        *(vector+realSize) = age;
        realSize++;
      }
    
      else {
          insert(vector, &realSize, age, position);
      }
    }
  }
}
