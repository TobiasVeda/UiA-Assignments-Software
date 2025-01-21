#include "mbed.h"
#include "DFRobot_RGBLCD1602.h"
#include "HTS221Sensor.h"
#include <cstdio>

volatile int state = 1;


void interrupt(){
    state = !state;
}

int main(){

    InterruptIn button(BUTTON1, PullNone);
    button.fall(&interrupt);

    I2C lcd_i2c_pins(D14, D15);
    //I2C ext_pins(SDA, SCL)
    DFRobot_RGBLCD1602 lcd(&lcd_i2c_pins, RGB_ADDRESS_V10_7BIT);

    lcd.init();
    lcd.display();
    lcd.clear();
    // Internal pinout document: pg10: hts is U6 
    // pg47: u6 is I2C2
    // pg38: I2C2 SDA:PB11, SCL:PB10
    // DevI2C??
    DevI2C hts_i2c_pins(PB_11, PB_10);
    //I2C internal_pins(SDA, SCL)
    HTS221Sensor hts(&hts_i2c_pins);

    if (hts.init(NULL) != 0) {
        printf("Failed to initialize HTS221 device!\n");
        }
        // Power up the HTS221 device
    if (hts.enable() != 0) {
        printf("Failed to power up HTS221 device!\n");
    }

    float temp;
    float humidity;
    int not_blue_hue;
    unsigned char degree[8] = {
        0b00111,
        0b00101,
        0b00111,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
    };
    lcd.customSymbol(0, degree);

    while (true) {
            hts.get_temperature(&temp);
            hts.get_humidity(&humidity);
            printf("Temperature: %f°C, Humidity: %f%%\n", temp, humidity);
            lcd.clear();

        if(state){
            lcd.printf("Temperature");
            lcd.setCursor(0,1);
            lcd.printf("%.1f C", temp);
            lcd.setCursor(4,1);
            lcd.write((unsigned char) 0);
            if (temp < 20) {
                lcd.setRGB(0, 0, 255);
            }else if (temp >= 20 && temp <= 24) {
                lcd.setRGB(252, 144, 3);
            }else if (temp > 24) {
                lcd.setRGB(255, 0, 0);
            }
        }else if (state == 0) {
            lcd.printf("Humidity");
            lcd.setCursor(0,1);
            lcd.printf("%.1f%%", humidity); 
            not_blue_hue = 255 * ((100-humidity) / 100);
            lcd.setRGB(not_blue_hue, not_blue_hue, 255);
            // Only changing blue would mean that at 0% the display would be off instead of white
        }

        thread_sleep_for(1000);
        
    }
}

