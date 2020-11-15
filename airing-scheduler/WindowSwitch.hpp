#ifndef WINDOWSWITCH_HPP
#define WINDOWSWITCH_HPP

#ifndef AVR
  #include <cstdint>
#endif
#include <Arduino.h>

class WindowSwitch {
  public:
    WindowSwitch(uint8_t switch_pin);
    void initialize();
    void handle_interrupt();

    bool update();
    bool is_open() const;

  private:
    uint8_t switch_pin;
    volatile bool change_flag = false;
    bool open;
};

#endif