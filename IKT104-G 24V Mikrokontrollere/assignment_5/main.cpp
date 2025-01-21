#include "mbed.h"
#include "DFRobot_RGBLCD1602/DFRobot_RGBLCD1602.h"
#include <chrono>
#include <cstdio>


Timeout timer;

    
void timer_cb(){
    static PwmOut buzzer(D1);   
    buzzer.period_ms(3); // tone
    buzzer.write(0.1); // volume
    timer.detach(); //don't know if does anything
}

int main(){
    timer.attach(&timer_cb, 61s);

    I2C lcd_i2c_pins(D14, D15);
    //I2C ext_pins(SDA, SCL)
    DFRobot_RGBLCD1602 lcd(&lcd_i2c_pins, RGB_ADDRESS_V10_7BIT);
    lcd.init();
    lcd.display();

    DigitalIn btn_1_pause(D5, PullUp);
    DigitalIn btn_2_reset(D4, PullUp);
    DigitalIn btn_3_add(D3, PullUp);
    DigitalIn btn_4_subtract(D2, PullUp);

    bool pause = 0;
    long long paused_time = 61;

    while (true) {
        long long time_left = chrono::duration_cast<chrono::seconds>(timer.remaining_time()).count();
        if (time_left < 0) {
            time_left = 0;
            // remaining_time return negative when time runs out
            // looks stupid on lcd, so sets it to 0 instead
        }
    
        if (pause) {
            timer.attach(&timer_cb, paused_time);
            // continually refresed with a value that does not change when pausing
        }else{
            paused_time = time_left;
            // paused time is only updated when not pausing
        }

        if(!btn_1_pause.read()){
            pause = !pause;
        }else if (!btn_2_reset.read()) {
            // can put a refresh here to make it set to 60 one loop earlier
            paused_time = 61;
            pause = 1;
        }else if(!btn_3_add.read()){         
            timer.attach(&timer_cb, (time_left += 5));
            paused_time += 5; // add during pausing
        }else if (!btn_4_subtract.read()) {
            // printf("subtract-");
            timer.attach(&timer_cb, (time_left -= 5));
            paused_time -= 5; // subtract during pausing
        }

        lcd.clear();
        lcd.printf("Time remaining");
        lcd.setCursor(0,1);
        lcd.printf("%llu", time_left);

        thread_sleep_for(100);
    }

}


