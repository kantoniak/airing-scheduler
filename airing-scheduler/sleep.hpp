#ifndef SLEEP_HPP
#define SLEEP_HPP

#include <avr/sleep.h>
#include <avr/interrupt.h>

// Based on https://www.re-innovation.co.uk/docs/sleep-modes-on-attiny85/

// Routines to set and clear bits (used in the sleep code)
#ifndef cbi
  #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void system_sleep() {

  // ADC off
  cbi(ADCSRA,ADEN);

  // Set sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  // Go to sleep
  sleep_mode();

  // Come back
  sleep_disable();

  // ADC on
  sbi(ADCSRA, ADEN);

}

#endif