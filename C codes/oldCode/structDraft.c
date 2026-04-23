#include <stdio.h>

typedef struct {
  
  int x;
  int y;
  
} typePoint;

int main() {
  
  typePoint p;
  
  typePoint *point = &p;
  
  printf("Please input a point in the R2 space\n<");
  scanf("%d %d", &(point->x), &(point->y));
  
  printf("\nPoint: (%d, %d)", point->x, point->y);
    
}
