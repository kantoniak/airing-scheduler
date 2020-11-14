#ifndef WINDOWSWITCH_HPP
#define WINDOWSWITCH_HPP

#ifndef AVR
  #include <cstdint>
#endif
#include <Arduino.h>

class WindowSwitch {
  public:
    WindowSwitch(uint8_t switch_pin) noexcept;
    void initialize() noexcept;
    void handle_interrupt() noexcept;

    bool update() noexcept;
    bool is_open() const noexcept;

  private:
    uint8_t switch_pin;
    volatile bool change_flag = false;
    bool open;
};

#endif