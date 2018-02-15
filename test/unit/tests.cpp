#include "Arduino.h"
#include "Util.h"
#include "unity_arduino.h"
#include "unity.h"
#include "tests.h"

#define BAUD_RATE 115200

void getClientID(){
  TEST_ASSERT_EQUAL_STRING("3303-0", Util::getClientID(3303,0));
}

void getOutputTopic() {
    TEST_ASSERT_EQUAL_STRING("3303/0/1/output", Util::getOutputTopic(3303, 0, 1));
}

void getInputTopic() {
    TEST_ASSERT_EQUAL_STRING("3303/0/1/input", Util::getInputTopic(3303, 0, 1));
}

void run_tests(){
  UNITY_BEGIN();
  RUN_TEST(getClientID);
  RUN_TEST(getOutputTopic);
  RUN_TEST(getInputTopic);
  UNITY_END();
}

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
