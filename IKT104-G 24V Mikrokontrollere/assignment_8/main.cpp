#include "mbed.h"
#include <chrono>
#include <cstdio>

typedef struct{
    public:
    int minute;
    int second;
    Mutex mutex;

} timer_t;

Thread t1(osPriorityNormal1, OS_STACK_SIZE, nullptr, "minute");
Thread t2(osPriorityNormal1, OS_STACK_SIZE, nullptr, "second");
Thread t3(osPriorityNormal, OS_STACK_SIZE, nullptr, "print");

void minute_counter(timer_t *timer){
    while (true) {
        ThisThread::sleep_for(60s);
        // one minute must pass before increase
        timer->mutex.lock();
        timer->minute++;
        timer->mutex.unlock();
    }
}
void second_counter(timer_t *timer){
    while (true) {
        ThisThread::sleep_for(1s);
        // one second must pass before increase
        timer->mutex.lock();
        timer->second++;
        if (timer->second == 60) {
            timer->second = 0;
        }
        timer->mutex.unlock();
    }
}
void print(timer_t *timer){
    while (true) {
        timer->mutex.lock();
        printf("Time passed: %d:%d\n", timer->minute, timer->second);
        timer->mutex.unlock();

        ThisThread::sleep_for(500ms); //twice per second
    }
}

int main(){
    timer_t timer = {.minute = 0, .second = 0};

    t1.start(callback(minute_counter, &timer));
    t2.start(callback(second_counter, &timer));
    t3.start(callback(print, &timer));

    t1.join();
    t2.join();
    t3.join();
}

