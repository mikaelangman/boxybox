#include <Arduino.h>
#include <IRremote.h>
#include <stdint.h>
#include "Actions.h"

const uint8_t RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;
decode_type_t ir_type = UNKNOWN;

void setup_ir(){

  Serial.write("Setup ir...");

  irrecv.enableIRIn();

  Serial.write("Setup ir done.");

}

uint8_t handle_ir(decode_results results){

  Serial.println(results.value, HEX);

  if (results.decode_type != ir_type){
    ir_type = results.decode_type;
  }


  return ACT_NOOP;

}

uint8_t loop_ir(uint8_t system_state){

  if (irrecv.decode(&results)){        
    irrecv.resume();
    return handle_ir(results);

  } else {
    return ACT_NOOP;
  }

}
