  #include <stdio.h>
  
  #define NONE -1
  #define MAX 1000
  
  int fillVector(int *vector);
  int searchSpeed(const int size, const int delSpeed, const int *vector);
  
  void showVector(int size, int *vector, const char *title);
  void deleteSpeed(int *size, int delSpeed, int *vector);
  void shiftLeft(int size, int position, int *vector);
  
  int main()
  {
  
    int vector[MAX];
    int delSpeed;
    int size = fillVector(vector);
    
    showVector(size, vector, "\n| Velocities vector |\n[ ");
    
    printf("Enter the speed to delete: \n");
    scanf("%d", &delSpeed);
    
    deleteSpeed(&size, delSpeed, vector);
    
    
    return 0;
  }
  
  void shiftLeft(int size, int position, int *vector) {
    
    for(int i=position; i<size-1; i++) {
      
      *(vector+i) = *(vector+i+1);
    }
    *(vector + size - 1) = 0;
  }
  
  int searchSpeed(const int size, const int delSpeed, const int *vector) {
    
    for(int i=0; i<size; i++) {
      
      if(*(vector+i) == delSpeed) return i;
      
    }
    
   return NONE; 
  }
  
  void deleteSpeed(int *size, int delSpeed, int *vector) {
    
    int position;
    int deleted = 0;
    
    while((position = searchSpeed(*size, delSpeed, vector)) != NONE) {
      
      shiftLeft(*size, position, vector);
      (*size)--;
      deleted=1;
    }
    
    if(!deleted) {
      printf("The number %d isn't present in the vector.", delSpeed);
    }
    
    else {
      
      showVector(*size, vector, "\n| New vector |\n[ ");
    }
    
  }
  
  void showVector(int size, int *vector, const char *title) {
    
    if(size<=0) {
      printf("Empty vector.");
      return;
    }
    
    printf("%s", title);
    
    for(int i=0; i<size-1; i++) {
      
      printf("%d, ", *(vector+i));
    }
    
    printf("%d ]\n", *(vector+size-1));
    printf("Total amount of speeds: %d\n", size);
    
  }
  
  int fillVector(int *vector) {
    
    int size=0, value;
    
    printf("Input all of the speeds, type 0 to stop: \n");
    
    do {
      
      scanf("%d", &value);
      if(value==0) break;
      
      *(vector+size) = value;
      
      size++;
      
    } while(value!=0);
    
    return size;
    
  }
