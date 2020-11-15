#ifndef CD4017_HPP
#define CD4017_HPP

#ifndef AVR
  #include <cstdint>
#endif
#include <Arduino.h>

class CD4017 {
  public:
    CD4017(uint8_t clock_pin, uint8_t reset_pin, uint8_t vcc_pin);
    void initialize();

    void turn_on();
    void turn_off();

    void increment();
    uint8_t get_value() const;
    uint8_t get_max_value() const;
    void set_value(uint8_t value);
    void reset();

  private:
    uint8_t clock_pin;
    uint8_t reset_pin;
    uint8_t vcc_pin;
    uint8_t value;

    bool power_on;

    void send_pulse(uint8_t pin) const;
};

#endif