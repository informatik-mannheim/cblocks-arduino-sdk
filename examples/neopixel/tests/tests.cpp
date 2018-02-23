#include "Arduino.h"
#include "CBlocks.h"
#include "Color.h"
#include "unity_arduino.h"
#include "unity.h"

#define BAUD_RATE 115200

void toJson(){
  Neopixel::Color c(127,5,130);
  JsonObject& json = c.toJson();

  TEST_ASSERT_EQUAL(127, json["red"]);
  TEST_ASSERT_EQUAL(5, json["green"]);
  TEST_ASSERT_EQUAL(130, json["blue"]);
}

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void run_tests(){
  UNITY_BEGIN();
  RUN_TEST(toJson);
  UNITY_END();
}

void setup(){
  initAndWaitForSerial();
  run_tests();
}

void loop(){
}
