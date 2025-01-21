#include "mbed.h"
#include <cstdio>

// main() runs in its own thread in the OS
int main()
{

// UnbufferedSerial pc(USBTX, USBRX, 115200);
DigitalIn button(D14);
AnalogIn meter(A0, 3.3f);

PwmOut red(D3);
PwmOut yellow(D2);
PwmOut green(D1);

red.period_ms(10);
yellow.period_ms(10);
green.period_ms(10);
float meter_value;
float a;
float b;
float c;
    while (true) {
        
        meter_value = meter.read();
        a = meter_value/0.33f;
        b = (meter_value-0.33f)/0.33f;
        c = (meter_value-0.67f)/0.33f;

        red.write(a-0.02); //make sure it can turn off
        yellow.write(b);
        green.write(c);

        if (button.read() < 0.9) {
            red.write(1);
            yellow.write(1);
            green.write(1);
        }
    

        thread_sleep_for(100);
        // with 100 ms delay and assuming a loop is instant, it have time for 10 loops a second
           
 
    }
}

