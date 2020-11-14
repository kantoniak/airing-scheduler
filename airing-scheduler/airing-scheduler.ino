#include "AiringTimer.hpp"
#include "Beeper.hpp"
#include "CD4017.hpp"

#define COUNTER_CLOCK_PIN 3
#define COUNTER_RESET_PIN 4
#define COUNTER_VCC_PIN 6
#define BEEPER_PIN 5

constexpr bool use_serial = false;

CD4017 counter(COUNTER_CLOCK_PIN, COUNTER_RESET_PIN, COUNTER_VCC_PIN);
Beeper beeper(BEEPER_PIN, 100, 250);
AiringTimer airing_timer(counter, 2000);

void setup() {
  if (use_serial) {
    Serial.begin(9600);
    Serial.println("START");
  }
  pinMode(LED_BUILTIN, OUTPUT);

  counter.initialize();
  beeper.initialize();

  delay(1000);
  airing_timer.start();
}

void loop() {
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
