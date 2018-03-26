#include "Arduino.h"
#include "CBlocks.h"
#include "TemperatureUtil.h"
#include "unity_arduino.h"
#include "unity.h"

#define BAUD_RATE 115200

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void run_tests(){
}

void setup(){
  initAndWaitForSerial();
  run_tests();
}

void loop(){
}
