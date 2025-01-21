#include <stdio.h> //printf, scanf
#include <stdlib.h> //qsort

int minimum(int array[]){
    return array[0];
}

int maximum(int array[], int length){
    int temp = 0;
    for (int i = 0; i < length; ++i) {
        temp = array[i];
    };
    return temp;
}

int sum(int array[], int length){
    int temp = 0;
    for (int i = 0; i < length; ++i) {
        temp += array[i];
    };
    return temp;
}

float average(int array[], int length){
    float temp = 0;
    for (int i = 0; i < length; ++i) {
        temp += array[i];
    };
    temp = temp / length;
    return temp;
}

float median(int array[], int length){
    float temp= array[4] + array[5];
    temp = temp/2;
    return temp;
}

int main() {
    int array[10];
    int length = sizeof(array)/sizeof(array[0]);

    for (int i = 0; i < length; ++i) {
        printf("Input number\n");
        scanf("%i",&array[i]);
    };

    int cmpfunc (const void * a, const void * b) {
        return ( *(int*)a - *(int*)b );
    };
    qsort(array, 10, sizeof(int), cmpfunc);

    printf("Minimum: %i", minimum(array));
    printf("\nMaximum: %i", maximum(array, length));
    printf("\nSum: %d", sum(array, length));
    printf("\nAverage: %g", average(array, length));
    printf("\nSorted: ");
    for (int i = 0; i < length; ++i) {
        printf("%i " , array[i]);
    }
    printf("\nMedian: %g", median(array, length));

}
