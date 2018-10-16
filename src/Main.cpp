#include <Arduino.h>
#include "Relays.h"
#include "Ir.h"
#include "Display.h"
#include "Actions.h"
#include "States.h"
#include "Phys_Input.h"
#include "Phys_Output.h"
#include <LowPower.h>

uint8_t system_state = STATE_OFF;

void stop_box(){
  if((system_state == STATE_OFF) || (system_state == STATE_TURNING_OFF)){
    return;
  }

  turn_all_relays_off();
  system_state = STATE_OFF;
  set_power_led(LOW);

}

void start_box(){
  if((system_state == STATE_ON) || (system_state == STATE_TURNING_ON)){
    return;
  }

  setup();

}

void toggle_power_state(){
  if((system_state == STATE_ON) || (system_state == STATE_TURNING_ON)){
    stop_box();
  } else {
    start_box();
  }
}


void perform_actions(uint8_t actions[]){

  for(uint8_t i; i < sizeof(actions); i++){

    if(system_state == STATE_OFF){
      if((actions[i] != ACT_TURN_ON) && (actions[i] != ACT_TOGGLE_POWER_STATE)){
        continue;
      }
    }

    switch(actions[i]){
      case ACT_NOOP:
        break;

      case ACT_TURN_OFF:
        stop_box();
        break;

      case ACT_TURN_ON:
        start_box();
        break;

      case ACT_TOGGLE_POWER_STATE:
        toggle_power_state();
        break;

      case ACT_ADV_INPUT:
        advance_input();
        break;

      case ACT_INC_VOL:
        turn_pot(true);
        break;

      case ACT_DEC_VOL:
        turn_pot(false);
        break;

      case ACT_STOP_POT:
        stop_pot();
        break;

      case ACT_UPDATE_DISPLAY:
        update_display(get_current_volume(), get_current_input());
        break;

      case ACT_SET_INPUT:
        set_input(get_wanted_input());
        break;

      default:
        break;
    }
  }
}

void setup(){

  Serial.begin(9600);
  Serial.write("Starting...");

  setup_ir();
  setup_relays();
  setup_phys_input();
  setup_phys_output();
  setup_display();

  Serial.write("Setup done.");

  system_state = STATE_ON;



}

void loop(){

  uint8_t actions[5] = {0,0,0,0,0};

  actions[0] = loop_ir(system_state);
  actions[2] = loop_phys_input(system_state);

  if (system_state == STATE_ON){
    actions[1] = loop_relays(system_state);
    actions[3] = loop_phys_output(system_state);
    actions[4] = loop_display(system_state);
  }

  perform_actions(actions);

}
