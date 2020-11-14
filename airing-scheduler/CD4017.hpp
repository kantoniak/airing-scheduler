#ifndef CD4017_HPP
#define CD4017_HPP

#ifndef AVR
  #include <cstdint>
#endif
#include <Arduino.h>

class CD4017 {
  public:
    CD4017(uint8_t clock_pin, uint8_t reset_pin) noexcept;
    void initialize() const noexcept;

    void increment() noexcept;
    uint8_t get_value() const noexcept;
    void set_value(uint8_t value) noexcept;
    void reset() noexcept;

  private:
    uint8_t clock_pin;
    uint8_t reset_pin;
    uint8_t value;

    void send_pulse(uint8_t pin) const noexcept;
};

#endif