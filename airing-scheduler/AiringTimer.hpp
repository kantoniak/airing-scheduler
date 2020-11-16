#ifndef AIRINGTIMER_HPP
#define AIRINGTIMER_HPP

#ifndef AVR
  #include <cstdint>
#endif
#include <arduino-timer.h>
#include "CD4017.hpp"

class AiringTimer {
  public:
    AiringTimer(CD4017& cd4017, const unsigned long airing_time);

    void start();
    void update();
    void stop();

    bool is_working() const;
    bool is_complete() const;

  private:
    Timer<1, millis, AiringTimer*> timer;
    CD4017& cd4017;
    const unsigned long airing_time;
    bool working;
    bool complete;

    static bool timer_update(AiringTimer*);
};

#endif