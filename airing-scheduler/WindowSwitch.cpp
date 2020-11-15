#include "WindowSwitch.hpp"

WindowSwitch::WindowSwitch(uint8_t switch_pin) : switch_pin(switch_pin) {
}

void WindowSwitch::initialize() {
    pinMode(this->switch_pin, INPUT_PULLUP);
    this->change_flag = true;
    this->update();
}

void WindowSwitch::handle_interrupt() {
    this->change_flag = true;
}

bool WindowSwitch::update() {
    if (!this->change_flag) {
        return false;
    }

    this->change_flag = false;
    this->open = digitalRead(this->switch_pin);
    return true;
}

bool WindowSwitch::is_open() const {
    return this->open;
}