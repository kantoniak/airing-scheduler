#include "WindowSwitch.hpp"

WindowSwitch::WindowSwitch(uint8_t switch_pin) noexcept : switch_pin(switch_pin) {
}

void WindowSwitch::initialize() noexcept {
    pinMode(this->switch_pin, INPUT_PULLUP);
    this->open = !digitalRead(this->switch_pin);
}

void WindowSwitch::handle_interrupt() noexcept {
    this->change_flag = true;
}

bool WindowSwitch::update() noexcept {
    if (!this->change_flag) {
        return false;
    }

    this->change_flag = false;
    this->open = !digitalRead(this->switch_pin);
    return true;
}

bool WindowSwitch::is_open() const noexcept {
    return this->open;
}