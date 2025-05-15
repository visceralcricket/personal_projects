#include <stdio.h>
#include <string.h> // needed for strcmp

int main() {
// %s es para referirse a arrays
char name[6];
printf("Hello! Could you tell me your name?: ");
scanf("%s", &name);
printf("Hi, %s!", name);

if (strcmp(name, "Felipe") == 0){
    printf("Oh! You have the same name that i do, haha!");
}

return 0;
}
