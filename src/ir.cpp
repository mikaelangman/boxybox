#include <Arduino.h>
#include <IRremote.h>
#include <stdint.h>
#include "Actions.h"
#include "IRCodes.h"

const uint8_t RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;
uint8_t wanted_input = 0;
uint8_t last_ir_action;

uint8_t get_wanted_input(){
  return wanted_input;
}

void setup_ir(){

  Serial.write("Setup ir...");

  irrecv.enableIRIn();

  Serial.write("Setup ir done.");

}

uint8_t ir2action(unsigned long ircode){

  uint8_t ret = ACT_NOOP;

  switch(ircode){

    case IR_ON: //On
      ret = ACT_TURN_ON;
      break;
    case IR_OFF: //Off
      ret = ACT_TURN_OFF;
      break;
    case IR_MUTE: //Mute
      ret = ACT_MUTE;
      break;
    case IR_VOL_UP: //Vol up
      ret = ACT_INC_VOL;
      break;
    case IR_VOL_DOWN: //Vol down
      ret = ACT_DEC_VOL;
      break;
    case IR_DISC: //Disc
      wanted_input = 0;
      ret = ACT_SET_INPUT;
      break;
    case IR_CD: //CD
      wanted_input = 1;
      ret = ACT_SET_INPUT;
      break;
    case IR_VIDEO: //Video
      wanted_input = 2;
      ret = ACT_SET_INPUT;
      break;
    case IR_AUX: //AUX
      wanted_input = 3;
      ret = ACT_SET_INPUT;
      break;
    case IR_TUNER: //Tuner
      break;
    case IR_TAPE: //Tape
      break;
    case IR_STOP: //Stop
      break;
    case IR_PAUSE: //Pause
      break;
    case IR_PLAY: //Play
      break;
    case IR_EJECT: //Eject
      break;
    case IR_REWIND: //Rewind
      break;
    case IR_FORWARD: //Forward
      break;

    case IR_REPEAT: //Repeated command
      ret = last_ir_action;   
      break;
    default:
      break;
  }

  if(ircode != IR_REPEAT){
    last_ir_action = ret;
  } 

  return ret;
}

uint8_t handle_ir(decode_results results){

  //Serial.println(results.value, HEX);
  return ir2action(results.value);

}

uint8_t loop_ir(uint8_t system_state){

  if (irrecv.decode(&results)){        
    irrecv.resume();
    return handle_ir(results);

  } else {
    return ACT_NOOP;
  }

}
