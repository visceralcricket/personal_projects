#define MAX_FILENAME 64
#define MAX_TIMESTAMP 32

#include "intRandomizer.h"

int main(void) {

    MKDIR("examples");
    int lb, ub, count;

    char filename[MAX_FILENAME];
    char timestamp[MAX_TIMESTAMP];

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H-%M-%S", t);

    int suffix = 0;
    for(;;) {
        if(suffix==0) snprintf(filename, sizeof(filename), "examples/%s.txt", timestamp);
        else snprintf(filename, sizeof(filename), "examples/%s_%d.txt", timestamp, suffix);

        FILE *test = fopen(filename, "r");
        if(!test) break;

        fclose(test);
        suffix++;
    }

    FILE *file = fopen(filename, "wt");
    if(!file) return 1;

    limpiarPantalla();

    printf("Enter the lower bound\n< ");
    if(fscanf(stdin, "%d", &lb) != 1) {
        fclose(file);
        remove(filename);
        limpiarPantalla();
        fprintf(stderr, "Fatal error: Invalid lower bound value. Program aborted.\n");
        exit(EXIT_FAILURE);
    }

    printf("\nEnter the upper bound\n< ");
    if(fscanf(stdin, "%d", &ub) != 1) exit(EXIT_FAILURE);

    printf("\nEnter the quantity of values desired\n< ");
    if(fscanf(stdin, "%d", &count) != 1) exit(EXIT_FAILURE);

    srand(time(NULL));
    int range = (ub - lb) + 1;
    for(int i=0; i<count; i++) {
        fprintf(file, "%d\n", (rand() % range) + lb);
    }

    fclose(file);
    return 0;
}