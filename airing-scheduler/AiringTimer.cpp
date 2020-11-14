#include "AiringTimer.hpp"

AiringTimer::AiringTimer(CD4017& cd4017, const size_t airing_time) noexcept : cd4017(cd4017), airing_time(airing_time) {
}

void AiringTimer::start() noexcept {
    this->complete = false;
    this->cd4017.turn_on();
    this->working = true;

    // Set timer to count upwards
    const size_t update_delta = (airing_time / this->cd4017.get_max_value()) + 1;
    this->timer.every(update_delta, AiringTimer::timer_update, this);
}

void AiringTimer::update() noexcept {
    this->timer.tick<void>();
}

void AiringTimer::stop() noexcept {
    timer.cancel();
    this->cd4017.turn_off();
    this->complete = false;
    this->working = false;
}

bool AiringTimer::is_working() const noexcept {
    return this->working;
}

bool AiringTimer::is_complete() const noexcept {
    return this->complete;
}

static bool AiringTimer::timer_update(AiringTimer* airing_timer) noexcept {
    if (airing_timer->cd4017.get_value() == airing_timer->cd4017.get_max_value()) {
        // Countdown complete
        airing_timer->timer.cancel();
        airing_timer->cd4017.turn_off();
        airing_timer->complete = true;
        airing_timer->working = false;
    } else {
        airing_timer->cd4017.increment();
    }
}
