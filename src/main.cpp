#include <Arduino.h>
#include "relays.h"
#include "ir.h"
#include "display.h"

void setup(){

  Serial.begin(9600);
  Serial.write("Starting...");

  //setup_ir();
  //setup_display();
  setup_relays();

  Serial.write("Setup done.");


}

void loop(){

  //loop_ir();
  //loop_display();
  loop_relays();

}
