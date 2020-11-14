#include "Beeper.hpp"

constexpr size_t BEEP_FREQ = 4000;

Beeper::Beeper(uint8_t pin, unsigned long beep_time, unsigned long total_time) noexcept : pin(pin), beep_time(beep_time), total_time(total_time) {
}

void Beeper::initialize() const noexcept {
    pinMode(this->pin, OUTPUT);
    this->stop();
}

void Beeper::start() noexcept {
    timer.every(total_time, Beeper::timer_beep, this);
}

void Beeper::update() noexcept {
    this->timer.tick();
}

void Beeper::stop() noexcept {
    timer.cancel();
    noTone(this->pin);
}

static bool Beeper::timer_beep(Beeper* beeper) noexcept {
    beeper->beep();
    return true;
}

void Beeper::beep() noexcept {
    tone(this->pin, BEEP_FREQ, this->beep_time);
}