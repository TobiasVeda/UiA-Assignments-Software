#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//    int num = 5;
//    int *pnum = &num;
//    *pnum = 7;
//
// *array == array[]

int main() {
int repeat;
printf("Input number of integers\n");
scanf("%d", &repeat);
if(repeat == 0){
    printf("No numbers were given");
    return 0;
};

int *array = malloc(repeat * sizeof(int));  // setter minneadresse med x størrelse


    for (int i = 0; i < repeat; ++i) {
        printf("Number %d:", i+1);
        scanf("%d", &array[i]);
    }

    printf("Count: %d\n", repeat);
    printf("Numbers: ");
    for (int i = 0; i < repeat; ++i) {
        printf("%d ", array[i]);
    }

    int cmpfunc (const void * a, const void * b) {
        return ( *(int*)a - *(int*)b );
    };
    qsort(array, repeat, sizeof(int), cmpfunc);

    printf("\nSorted: ");
    for (int i = 0; i < repeat; ++i) {
        printf("%d ", array[i]);
    }
    free(array);

}
