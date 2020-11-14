#include "CD4017.hpp"

#define COUNTER_CLOCK_PIN 3
#define COUNTER_RESET_PIN 4

constexpr bool use_serial = false;

CD4017 counter(COUNTER_CLOCK_PIN, COUNTER_RESET_PIN);

void setup() {
  if (use_serial) {
    Serial.begin(9600);
    Serial.println("START");
  }
  pinMode(LED_BUILTIN, OUTPUT);

  counter.initialize();
}

// the loop function runs over and over again forever
void loop() {
  if (use_serial) {
    Serial.println("LOOP");
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  counter.increment();
  delay(250);
}
