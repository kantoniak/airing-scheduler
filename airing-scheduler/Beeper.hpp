#ifndef BEEPER_HPP
#define BEEPER_HPP

#ifndef AVR
  #include <cstdint>
#endif
#include <Arduino.h>
#include <arduino-timer.h>

class Beeper {
  public:
    Beeper(uint8_t pin, unsigned long beep_time, unsigned long total_time);
    void initialize();

    void start();
    void update();
    void stop();

  private:
    Timer<1, millis, Beeper*> timer;
    uint8_t pin;
    unsigned long beep_time;
    unsigned long total_time;

    static bool timer_beep(Beeper*);
    void beep();
};

#endif