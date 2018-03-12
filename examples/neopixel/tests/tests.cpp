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

void importJson(){
  DynamicJsonBuffer buffer;
  JsonObject& json = buffer.createObject();

  json["red"] = 127;
  json["green"] = 5;
  json["blue"] = 130;

  Neopixel::Color c = {0,0,0};
  c.importJson(json);

  TEST_ASSERT_EQUAL(127, c.red);
  TEST_ASSERT_EQUAL(5, c.green);
  TEST_ASSERT_EQUAL(130, c.blue);
}

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void run_tests(){
  UNITY_BEGIN();
  RUN_TEST(toJson);
  RUN_TEST(importJson);
  UNITY_END();
}

void setup(){
  initAndWaitForSerial();
  run_tests();
}

void loop(){
}
