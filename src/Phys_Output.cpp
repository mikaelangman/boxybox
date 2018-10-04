#include <Arduino.h>
#include <stdint.h>
#include "Actions.h"

#define MOTOR_PIN_POS 12
#define MOTOR_PIN_NEG 11
#define MOTOR_PIN_PWM 10
#define PWM_DUTY_CYCLE 255
#define TURNING_TIME 200
#define POWER_LED_PIN 4

int turning_pot = 0;

void set_power_led(uint8_t state){
    digitalWrite(POWER_LED_PIN, state);
}

void turn_pot(bool positive_direction){

    digitalWrite(MOTOR_PIN_NEG, !positive_direction);
    digitalWrite(MOTOR_PIN_POS, positive_direction);
    analogWrite(MOTOR_PIN_PWM, PWM_DUTY_CYCLE);
    turning_pot = TURNING_TIME;

}

void stop_pot(){

    analogWrite(MOTOR_PIN_PWM, 0);
    digitalWrite(MOTOR_PIN_NEG, LOW);
    digitalWrite(MOTOR_PIN_POS, LOW);

}

void setup_phys_output(){

    Serial.write("Setup phys output...");

    pinMode(MOTOR_PIN_PWM, OUTPUT);
    pinMode(MOTOR_PIN_NEG, OUTPUT);
    pinMode(MOTOR_PIN_POS, OUTPUT);
    pinMode(POWER_LED_PIN, OUTPUT);
    set_power_led(HIGH);

    Serial.write("Setup phys output done.");

}
uint8_t loop_phys_output(uint8_t system_state){

    if(turning_pot > 0){
        turning_pot = turning_pot - 1;
        
        if (turning_pot == 0){
            return ACT_STOP_POT;
        }
    }

    return ACT_NOOP;
}

