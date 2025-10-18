#include <stdio.h>
#include <stdbool.h>

#define MAX 100

void bubbleSort(int size, int *numbers);
void swap(int i, int *numbers);

int main() {
    
    int size;
    
    printf("Please input the size of the numbers to store and sort:\n");
    scanf("%d", &size);
    
    int numbers[size];
    
    for(int i=0; i<size; i++) {
      
      scanf("%d", (numbers+i));
      
    }
    
    bubbleSort(size, numbers);
    
    printf("\nSorted numbers:\n");
    
    for(int i=0; i<size; i++) {
      
      printf("%d ", *(numbers+i));
      
    }
    
    return 0;
}

void swap(int i, int *numbers) {
  
  int supportValue = *(numbers+i);
  
  *(numbers+i) = *(numbers+i+1);
  *(numbers+i+1) = supportValue;
  
}

void bubbleSort(int size, int *numbers) {
  
  bool swapped = false;

  do {
    
    swapped = false;
    
    for(int k=0; k<(size-1); k++) {
      
      if(*(numbers+k) > *(numbers+k+1)) {
        
        swap(k, numbers);
        swapped = true;
      }
      
    }

  } while(swapped);
  
}
