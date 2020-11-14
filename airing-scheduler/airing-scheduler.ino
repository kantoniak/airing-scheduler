#include "AiringTimer.hpp"
#include "Beeper.hpp"
#include "CD4017.hpp"
#include "WindowSwitch.hpp"

#define SWITCH_PIN 2
#define COUNTER_CLOCK_PIN 3
#define COUNTER_RESET_PIN 4
#define COUNTER_VCC_PIN 6
#define BEEPER_PIN 5

constexpr bool use_serial = true;

WindowSwitch window_switch(SWITCH_PIN);
CD4017 counter(COUNTER_CLOCK_PIN, COUNTER_RESET_PIN, COUNTER_VCC_PIN);
AiringTimer airing_timer(counter, 2000);
Beeper beeper(BEEPER_PIN, 100, 250);

void setup() {
  if (use_serial) {
    Serial.begin(9600);
    Serial.println("START");
  }
  pinMode(LED_BUILTIN, OUTPUT);

  window_switch.initialize();
  counter.initialize();
  beeper.initialize();

  /*
  delay(1000);
  airing_timer.start();
  */

  if (use_serial) {
    Serial.println("Window open: " + String(window_switch.is_open()));
  }
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), on_switch, CHANGE);
}

void loop_old() {
  if (use_serial) {
    Serial.println("LOOP");
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  if (airing_timer.is_complete()) {
    if (use_serial) {
      Serial.println("COMPLETE");
    }
    airing_timer.stop();
    beeper.start();
  } else if (airing_timer.is_working()) {
    if (use_serial) {
      Serial.println("UPDATE");
    }
    airing_timer.update();
  } else {
    beeper.update();
  }

  if (millis() > 5000) {
    beeper.stop();
  }
}

void on_switch() {
  window_switch.handle_interrupt();
  if (use_serial) {
    Serial.println("INTERRUPT");
  }
}

void loop() {
  if (window_switch.update()) {
    digitalWrite(LED_BUILTIN, window_switch.is_open());
    if (use_serial) {
      Serial.println("Window open: " + String(window_switch.is_open()));
    }
  }
}