#include "AiringTimer.hpp"
#include "Beeper.hpp"
#include "CD4017.hpp"
#include "WindowSwitch.hpp"
#include "sleep.hpp"

#undef _DEBUG
#define ATTINY85

#ifdef ATTINY85
  #define SWITCH_PIN 2
  #define SWITCH_INT 0
  #define COUNTER_CLOCK_PIN 0
  #define COUNTER_RESET_PIN 1
  #define COUNTER_VCC_PIN 3
  #define BEEPER_PIN 4
  #define ATTINY85_WINDOW_SLEEP_TIME 1000
#endif

#ifdef ARDUINO_NANO
  #define SWITCH_PIN 2
  #define SWITCH_INT 0
  #define COUNTER_CLOCK_PIN 3
  #define COUNTER_RESET_PIN 4
  #define COUNTER_VCC_PIN 6
  #define BEEPER_PIN 5
#endif

#define COUNTDOWN_TIME (15 * 60 * 1000UL)
#define COUNTING_DELAY (15 * 1000UL)
#define BEEPER_BEEP_LENGTH 100
#define BEEPER_TOTAL_LENGTH 250
#define BEEPING_DELAY 30

enum State {
  WAITING = 0,
  COUNTING = 1,
  ALERTING = 2
};

State state;
WindowSwitch window_switch(SWITCH_PIN);
CD4017 counter(COUNTER_CLOCK_PIN, COUNTER_RESET_PIN, COUNTER_VCC_PIN);
AiringTimer airing_timer(counter, COUNTDOWN_TIME);
Beeper beeper(BEEPER_PIN, BEEPER_BEEP_LENGTH, BEEPER_TOTAL_LENGTH);

void log(String message) {
#ifdef _DEBUG
  Serial.println(message);
#endif
}

void to_waiting() {
  log("to_waiting"); delay(500);
  state = WAITING;
  airing_timer.stop();
  beeper.stop();
  window_switch.handle_interrupt();
}

void from_waiting_to_counting() {
  log("from_waiting_to_counting");
  state = COUNTING;
  airing_timer.start();
  beeper.stop();
}

void from_counting_to_alterting() {
  log("from_counting_to_alterting");
  state = ALERTING;
  airing_timer.stop();
  beeper.start();
}

void on_switch() {
  window_switch.handle_interrupt();
  log("INTERRUPT");
}

void setup() {
#ifdef _DEBUG
    Serial.begin(9600);
    log("START");
#endif

  window_switch.initialize();
  counter.initialize();
  beeper.initialize();

  attachInterrupt(SWITCH_INT, on_switch, CHANGE);

  // Initially set WAITING state and trigger update
  to_waiting();
}

void loop() {
  switch (state) {
    case WAITING: {
      if (window_switch.update() && window_switch.is_open()) {
        from_waiting_to_counting();
        break;
      } else {
        #ifdef ARDUINO_NANO
        system_sleep();
        #endif
        #ifdef ATTINY85
        delay(ATTINY85_WINDOW_SLEEP_TIME);
        #endif
      }
      break;
    }

    case COUNTING: {
      if (window_switch.update() && !window_switch.is_open()) {
        to_waiting();
        break;
      }

      airing_timer.update();
      if (airing_timer.is_complete()) {
        from_counting_to_alterting();
        break;
      }

      delay(COUNTING_DELAY);
      break;
    }

    case ALERTING: {
      if (window_switch.update() && !window_switch.is_open()) {
        to_waiting();
        break;
      }

      beeper.update();
      delay(BEEPING_DELAY);
      break;
    }
    
    default: {
      // Should never get here
      while (true);
    }
  }
}