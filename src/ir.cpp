#include <Arduino.h>
#include <IRremote.h>
#include <stdint.h>

const uint8_t RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup_ir(){
  //Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop_ir(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}
