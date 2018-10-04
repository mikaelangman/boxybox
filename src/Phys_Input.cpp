#include <Arduino.h>
#include <stdint.h>
#include "Actions.h"

#define INPUT_BUTTON_PIN 2
#define POWER_BUTTON_PIN 4
#define VOL_PIN A0
#define VOL_SENSOR_MAX 0
#define VOL_SENSOR_MIN 1023


uint8_t get_current_volume(){

    return map(analogRead(VOL_PIN), VOL_SENSOR_MIN, VOL_SENSOR_MAX, 0, 100);
}

void setup_phys_input(){

    Serial.write("Setup phys inputs...");

    pinMode(INPUT_BUTTON_PIN, INPUT);
    pinMode(POWER_BUTTON_PIN, INPUT);

    Serial.write("Setup phys inputs done.");



}
uint8_t loop_phys_input(uint8_t system_state){

    if(digitalRead(INPUT_BUTTON_PIN) == HIGH){
        return ACT_ADV_INPUT;

    } else if (digitalRead(POWER_BUTTON_PIN) == HIGH){
        return ACT_TOGGLE_POWER_STATE;
    }

    return ACT_NOOP;
}
