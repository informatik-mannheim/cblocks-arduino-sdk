#include "Arduino.h"
#include "tests.h"

#define BAUD_RATE 115200

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void setup(){
  initAndWaitForSerial();
  run_tests();
}

void loop(){
}
