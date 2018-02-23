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

void isValidJsonReturnsTrueIfAllElementsPresent(){
  DynamicJsonBuffer buffer;
  JsonObject& json = buffer.createObject();

  json["red"] = 127;
  json["green"] = 5;
  json["blue"] = 130;

  TEST_ASSERT_TRUE(Neopixel::Color::isValidJson(json));
}

void isValidJsonReturnsFalseIfBlueIsMissing(){
  DynamicJsonBuffer buffer;
  JsonObject& json = buffer.createObject();

  json["red"] = 127;
  json["green"] = 5;

  TEST_ASSERT_FALSE(Neopixel::Color::isValidJson(json));
}

void validateJsonReturnsErrorMessageIfGreenIsMissing(){
  DynamicJsonBuffer buffer;
  JsonObject& json = buffer.createObject();

  json["red"] = 127;
  json["blue"] = 130;

  TEST_ASSERT_EQUAL_STRING("Please set element green.", Neopixel::Color::validateJson(json).c_str());
}

void validateJsonReturnsErrorMessageIfRedIsAString(){
  DynamicJsonBuffer buffer;
  JsonObject& json = buffer.createObject();

  json["red"] = "test";
  json["blue"] = 130;
  json["green"] = 5;

  TEST_ASSERT_EQUAL_STRING("red must be a number between 0 and 255.", Neopixel::Color::validateJson(json).c_str());
}

void validateJsonReturnsErrorMessageIfRedIs256(){
  DynamicJsonBuffer buffer;
  JsonObject& json = buffer.createObject();

  json["red"] = 256;
  json["blue"] = 130;
  json["green"] = 5;

  TEST_ASSERT_EQUAL_STRING("red must be a number between 0 and 255.", Neopixel::Color::validateJson(json).c_str());
}

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void run_tests(){
  UNITY_BEGIN();
  RUN_TEST(toJson);
  RUN_TEST(isValidJsonReturnsTrueIfAllElementsPresent);
  RUN_TEST(isValidJsonReturnsFalseIfBlueIsMissing);
  RUN_TEST(validateJsonReturnsErrorMessageIfGreenIsMissing);
  RUN_TEST(validateJsonReturnsErrorMessageIfRedIsAString);
  RUN_TEST(validateJsonReturnsErrorMessageIfRedIs256);
  UNITY_END();
}

void setup(){
  initAndWaitForSerial();
  run_tests();
}

void loop(){
}
