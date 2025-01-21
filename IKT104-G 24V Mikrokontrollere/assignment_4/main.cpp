#include "mbed.h"
#include "DFRobot_RGBLCD1602/DFRobot_RGBLCD1602.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>

volatile bool do_watchdog_refresh = 0;
volatile bool do_pause = 0;

void reset_watchdog(){
    do_watchdog_refresh = !do_watchdog_refresh;
}
void pause(){
    do_pause = !do_pause;
}

int main(){

    I2C lcd_i2c_pins(D14, D15);
    //I2C ext_pins(SDA, SCL)
    DFRobot_RGBLCD1602 lcd(&lcd_i2c_pins, RGB_ADDRESS_V10_7BIT);
    lcd.init();
    lcd.display();

    InterruptIn btn_reset(D5, PullUp);
    btn_reset.fall(&reset_watchdog);

    InterruptIn btn_pause(BUTTON1, PullNone);
    btn_pause.fall(&pause);

    Timer timer;
    timer.start();

    Watchdog &watchdog = Watchdog::get_instance();
    watchdog.start(10000);
    

    // printf("new\n");
    while (true) {
        long long time_passed = chrono::duration_cast<chrono::milliseconds>(timer.elapsed_time()).count();
        static float time_in_seconds;
        time_in_seconds = time_passed / 1000.0f;

        lcd.clear();
        lcd.printf("Time: %.2f", time_in_seconds);


        if(do_pause){
            watchdog.kick();
            timer.stop();
            // printf("stop\n");
        }else{
            timer.start();
        }


        if (do_watchdog_refresh) {
            watchdog.kick(); //:(
            do_watchdog_refresh = !do_watchdog_refresh;
            // printf("kick\n");
        }

         thread_sleep_for(100);
        // can't remember if thread_sleep_for puts it in deep sleep or not, 
        // but Timer should prevent deep sleep
    }
}
