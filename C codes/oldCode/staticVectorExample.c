#include <stdio.h>
#define MAX_NUMBERS 10

unsigned long long factorial(unsigned short a);

int main()
{
  
  unsigned short numbers [MAX_NUMBERS] = {0};
  unsigned short i;
  
  printf("Original Array :");
  
  for(i=0; i<MAX_NUMBERS;i++) {
    printf(" %hu |", numbers[i]);
  }
  
  printf("\n\nArray of factorials from inputted values : ");
  
  
  for(i=0; i < MAX_NUMBERS; i++) {
    scanf("%hu", &numbers[i]);
  }
  
  for(i=0; i<MAX_NUMBERS; i++) {
    printf("%llu | ", factorial(numbers[i]));
  }
  
}

unsigned long long factorial(unsigned short a) {
  if(a<=1) {
    return 1;
  }
  
  return a*factorial(a-1);
  
}
