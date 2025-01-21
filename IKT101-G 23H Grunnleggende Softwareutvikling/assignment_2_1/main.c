#include <stdio.h>

int count = 0;
float sum = 0;
float average = 0;
float input = 0;

float input_loop(){
    count++;
    printf("Write a number\n");
    scanf("%f", &input);

    if (input != 0) {
        sum += input;
        input_loop();
    }

}

int main() {

    input_loop();

    count = count - 1;
    average = sum/count;


    printf("Count: %d \n", count);
    printf("Sum: %g \n", sum);
    printf("Average: %g \n", average);


}
