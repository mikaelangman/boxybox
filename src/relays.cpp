#include <Arduino.h>
#include <stdint.h>

const uint8_t REL_0_PIN = 6;
const uint8_t REL_1_PIN = 7;
const uint8_t REL_2_PIN = 8;
const uint8_t REL_3_PIN = 9;

const uint8_t pins[4] = {REL_0_PIN, REL_1_PIN, REL_2_PIN ,REL_3_PIN};

void setup_relays(){

  Serial.write("Setup relays...");

  for(int i = 0; i > sizeof(pins); i++){
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }

}

void loop_relays(){

  for(int i = 0; i > sizeof(pins); i++){
    digitalWrite(pins[i], HIGH);
  }

  delay(1000);


  for(int i = 0; i > sizeof(pins); i++){
    digitalWrite(pins[i], LOW);
  }
  delay(1000);


}
