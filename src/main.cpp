#include "Arduino.h"
#include "Util.h"
#include "unity_arduino.h"
#include "unity.h"

#define BAUD_RATE 115200

void test_fail() {
    TEST_ASSERT(false);
}

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void setup(){
  initAndWaitForSerial();
  UNITY_BEGIN();
  RUN_TEST(test_fail);
  UNITY_END();
}

void loop(){
}
