#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    // get the input file
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file\n");
        return 1;
    }

    // allocate memory for the two arrays
    int *a = (int*)malloc(1000*sizeof(int));
    int *b = (int*)malloc(1000*sizeof(int));
    int i = 0;
    // until end of file get the inputs
    while(!feof(input)) {
        fscanf(input, "%d   %d", &a[i], &b[i]);
        i++;
    }

    for(int i = 0; i < 1000; i++) {
        printf("%d   %d\n", a[i], b[i]);
    }

    // free the memory and close the file
    free(a);
    free(b);
    fclose(input);


    return 0;
}
