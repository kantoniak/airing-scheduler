#include "CD4017.hpp"

constexpr size_t PULSE_DURATION = 1; // Microseconds
constexpr size_t MAX_VALUE = 3;

CD4017::CD4017(uint8_t clock_pin, uint8_t reset_pin) noexcept : value(0), clock_pin(clock_pin), reset_pin(reset_pin) {
}

void CD4017::initialize() const noexcept {
    pinMode(this->clock_pin, OUTPUT);
    pinMode(this->reset_pin, OUTPUT);
    digitalWrite(this->clock_pin, LOW);
    digitalWrite(this->reset_pin, LOW);
    this->reset();
}

void CD4017::increment() noexcept {
    if (this->value == MAX_VALUE) {
        this->reset();
    } else {
        this->send_pulse(this->clock_pin);
        this->value++;
    }
}

uint8_t CD4017::get_value() const noexcept {
    return this->value;
}

void CD4017::set_value(uint8_t value) noexcept {
    if (value > MAX_VALUE) {
        value %= MAX_VALUE;
    }
    if (value < this->value) {
        this->reset();
    }
    while (this->value < value) {
        // Increment skipping comparison with MAX_VALUE
        this->send_pulse(this->clock_pin);
        this->value++;
    }
}

void CD4017::reset() noexcept {
    this->send_pulse(this->reset_pin);
    this->value = 0;
}

void CD4017::send_pulse(uint8_t pin) const noexcept {
    digitalWrite(pin, HIGH);
    delayMicroseconds(PULSE_DURATION);
    digitalWrite(pin, LOW);
    delayMicroseconds(PULSE_DURATION);
}