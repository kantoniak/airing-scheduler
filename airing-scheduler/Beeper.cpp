#include "Beeper.hpp"

#define BEEP_FREQ 3000

Beeper::Beeper(uint8_t pin, unsigned long beep_time, unsigned long total_time) : pin(pin), beep_time(beep_time), total_time(total_time) {
}

void Beeper::initialize() {
    pinMode(this->pin, OUTPUT);
    this->stop();
}

void Beeper::start() {
    timer.every(total_time, Beeper::timer_beep, this);
}

void Beeper::update() {
    this->timer.tick<void>();
}

void Beeper::stop() {
    timer.cancel();
    noTone(this->pin);
}

bool Beeper::timer_beep(Beeper* beeper) {
    beeper->beep();
    return true;
}

void Beeper::beep() {
    tone(this->pin, BEEP_FREQ, this->beep_time);
}