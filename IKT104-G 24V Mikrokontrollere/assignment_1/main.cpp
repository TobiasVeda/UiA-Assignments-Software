// led 20mA 3.3V-2V 1.3V/0.02mA=65ohm
#include "mbed.h"
#include <cstdio>


DigitalOut led(D1);
UnbufferedSerial pc(USBTX, USBRX, 115200);

int main() {
    
    led = 1;

    while(true){

        char input; 
        // char is one byte

        printf("Skriv inn:");
        scanf("%c", &input);
         printf("\n");

        if (input) {
        led = 1;
        } else if (input == 0) {
        led = 0;
        }
    }
    
    
}