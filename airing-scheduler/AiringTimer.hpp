#ifndef AIRINGTIMER_HPP
#define AIRINGTIMER_HPP

#ifndef AVR
  #include <cstdint>
#endif
#include <arduino-timer.h>
#include "CD4017.hpp"

class AiringTimer {
  public:
    AiringTimer(CD4017& cd4017, const size_t airing_time) noexcept;

    void start() noexcept;
    void update() noexcept;
    void stop() noexcept;

    bool is_working() const noexcept;
    bool is_complete() const noexcept;

  private:
    Timer<1, millis, AiringTimer*> timer;
    CD4017& cd4017;
    const size_t airing_time;
    bool working;
    bool complete;

    static bool timer_update(AiringTimer*) noexcept;
};

#endif