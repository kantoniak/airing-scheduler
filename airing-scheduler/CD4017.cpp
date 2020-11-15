#include "CD4017.hpp"

#define PULSE_DURATION 1
#define MAX_VALUE 9

CD4017::CD4017(uint8_t clock_pin, uint8_t reset_pin, uint8_t vcc_pin) : value(0), clock_pin(clock_pin), reset_pin(reset_pin), vcc_pin(vcc_pin) {
}

void CD4017::initialize() {
    pinMode(this->clock_pin, OUTPUT);
    pinMode(this->reset_pin, OUTPUT);
    pinMode(this->vcc_pin, OUTPUT);
    digitalWrite(this->clock_pin, LOW);
    digitalWrite(this->reset_pin, LOW);
    digitalWrite(this->vcc_pin, LOW);
    this->reset();
}

void CD4017::turn_on() {
    digitalWrite(this->vcc_pin, HIGH);
    this->power_on = true;
    this->reset();
}

void CD4017::turn_off() {
    digitalWrite(this->vcc_pin, LOW);
    this->power_on = false;
    this->value = 0;
}

void CD4017::increment() {
    if (!this->power_on) {
        return;
    }

    if (this->value == MAX_VALUE) {
        this->reset();
    } else {
        this->send_pulse(this->clock_pin);
        this->value++;
    }
}

uint8_t CD4017::get_value() const {
    return this->value;
}

uint8_t CD4017::get_max_value() const {
    return MAX_VALUE;
}

void CD4017::set_value(uint8_t value) {
    if (!this->power_on) {
        return;
    }

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

void CD4017::reset() {
    if (!this->power_on) {
        return;
    }

    this->send_pulse(this->reset_pin);
    this->value = 0;
}

void CD4017::send_pulse(uint8_t pin) const {
    digitalWrite(pin, HIGH);
    delayMicroseconds(PULSE_DURATION);
    digitalWrite(pin, LOW);
    delayMicroseconds(PULSE_DURATION);
}