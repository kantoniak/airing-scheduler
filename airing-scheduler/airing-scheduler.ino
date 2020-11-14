#include "CD4017.hpp"
#include "Beeper.hpp"

#define COUNTER_CLOCK_PIN 3
#define COUNTER_RESET_PIN 4
#define BEEPER_PIN 5

constexpr bool use_serial = false;

CD4017 counter(COUNTER_CLOCK_PIN, COUNTER_RESET_PIN);
Beeper beeper(BEEPER_PIN, 100, 250);

void setup() {
  if (use_serial) {
    Serial.begin(9600);
    Serial.println("START");
  }
  pinMode(LED_BUILTIN, OUTPUT);

  counter.initialize();
  beeper.initialize();
  beeper.start();
}

// the loop function runs over and over again forever
void loop() {
  if (use_serial) {
    Serial.println("LOOP");
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  beeper.update();

  if (millis() > 2000) {
    beeper.stop();
  }
}
