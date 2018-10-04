#include <Arduino.h>
#include <stdint.h>
#include "Actions.h"

#define REL_0_PIN 6
#define REL_1_PIN 7
#define REL_2_PIN 8
#define REL_3_PIN 9
#define NUM_INPUTS 4

const uint8_t pins[4] = {REL_0_PIN, REL_1_PIN, REL_2_PIN ,REL_3_PIN};
uint8_t current_input = 0;

void turn_relay_off(uint8_t rel){

      digitalWrite(pins[rel], LOW);


}

void turn_relay_on(uint8_t rel){

      digitalWrite(pins[rel], HIGH);


}

void turn_all_relays_off(){

    for(uint8_t i = 0; i < sizeof(pins); i++){
    digitalWrite(pins[i], LOW);
  }
}

void advance_input(){

  turn_relay_off(current_input);
  current_input = (current_input + 1) % (NUM_INPUTS - 1);
  turn_relay_on(current_input);
}

void setup_relays(){

  Serial.write("Setup relays...");


  for(uint8_t i = 0; i < sizeof(pins); i++){
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  } 

  turn_all_relays_off();
  turn_relay_on(current_input);

  Serial.write("Setup relays done.");

}

uint8_t loop_relays(uint8_t system_state){

  return ACT_NOOP;

}

