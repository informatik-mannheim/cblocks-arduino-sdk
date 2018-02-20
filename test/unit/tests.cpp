#include "Arduino.h"
#include "Util.h"
#include "unity_arduino.h"
#include "unity.h"
#include "tests.h"

#define BAUD_RATE 115200

void getClientID(){
  TEST_ASSERT_EQUAL_STRING("3303-0", Util::getClientID(3303,0).c_str());
}

void getOutputTopic() {
  TEST_ASSERT_EQUAL_STRING("3303/0/1/output", Util::getOutputTopic(3303, 0, 1).c_str());
}

void getInputTopic() {
  TEST_ASSERT_EQUAL_STRING("3303/0/1/input", Util::getInputTopic(3303, 0, 1).c_str());
}

void getNamedTopic() {
  TEST_ASSERT_EQUAL_STRING("3303/0/status", Util::getNamedTopic(3303, 0, String("status")).c_str());
}

void getIntegerPayload(){
  unsigned int value = 55;
  TEST_ASSERT_EQUAL_STRING("55", Util::getPayloadFor(value).c_str());
}

void getFloatPayload(){
  TEST_ASSERT_EQUAL_STRING("55.00", Util::getPayloadFor(55.0f).c_str());
}

void getJSONPayload(){
  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps";
  root["time"] = 1351824120;

  JsonArray& data = root.createNestedArray("data");
  data.add(48.756080);
  data.add(2.302038);

  String payload = Util::getPayloadFor(root);
  TEST_ASSERT_EQUAL_STRING("{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.75608,2.302038]}", payload.c_str());
}

void getLastWill(){
  Will will = Util::getLastWillFor(3303, 0);
  TEST_ASSERT_EQUAL_STRING("3303/0/status", will.topic.c_str());
  TEST_ASSERT_EQUAL(2, will.qos);
  TEST_ASSERT_TRUE(will.retain);
  TEST_ASSERT_EQUAL_STRING("offline", will.message.c_str());
}

void getFirstWill(){
  Will will = Util::getFirstWillFor(3303, 0);
  TEST_ASSERT_EQUAL_STRING("3303/0/status", will.topic.c_str());
  TEST_ASSERT_EQUAL(2, will.qos);
  TEST_ASSERT_TRUE(will.retain);
  TEST_ASSERT_EQUAL_STRING("online", will.message.c_str());
}

void validateCommandJSONReturnsEmptyStringIfValid(){
  DynamicJsonBuffer buffer;

  String json("{\"requestID\": 4711,\"clientID\": \"node-red\",\"data\": {\"value\": true}}");

  TEST_ASSERT_EQUAL_STRING("", Util::validateCommandJSON(json, buffer).c_str());
}

void validateCommandJSONReturnsFailureIfRequestIDIsMissing(){
  DynamicJsonBuffer buffer;

  String json("{\"clientID\": \"node-red\",\"data\": {\"value\": true}}");

  TEST_ASSERT_EQUAL_STRING("Command has no \"requestID\".", Util::validateCommandJSON(json, buffer).c_str());
}

void validateCommandJSONReturnsFailureIfRequestIDIsNotALong(){
  DynamicJsonBuffer buffer;

  String json("{\"requestID\": true,\"clientID\": \"node-red\",\"data\": {\"value\": true}}");

  TEST_ASSERT_EQUAL_STRING("\"requestID\" must be of type long.", Util::validateCommandJSON(json, buffer).c_str());
}

void validateCommandJSONReturnsFailureIfClientIDIsMissing(){
  DynamicJsonBuffer buffer;

  String json("{\"requestID\": 4711, \"data\": {\"value\": true}}");

  TEST_ASSERT_EQUAL_STRING("Command has no \"clientID\".", Util::validateCommandJSON(json, buffer).c_str());
}

void validateCommandJSONReturnsFailureIfClientIDIsNotAString(){
  DynamicJsonBuffer buffer;

  String json("{\"requestID\": 4711,\"clientID\": 1234,\"data\": {\"value\": true}}");

  TEST_ASSERT_EQUAL_STRING("\"clientID\" must be of type String.", Util::validateCommandJSON(json, buffer).c_str());
}

void validateCommandJSONReturnsFailureIfDataIsMissing(){
  DynamicJsonBuffer buffer;

  String json("{\"requestID\": 4711,\"clientID\": \"node-red\"}");

  TEST_ASSERT_EQUAL_STRING("Command has no \"data\".", Util::validateCommandJSON(json, buffer).c_str());
}

void validateCommandJSONReturnsFailureIfDataIsNoJSON(){
  DynamicJsonBuffer buffer;

  String json("{\"requestID\": 4711,\"clientID\": \"node-red\",\"data\": true}");

  TEST_ASSERT_EQUAL_STRING("Data is invalid JSON.", Util::validateCommandJSON(json, buffer).c_str());
}

void run_tests(){
  UNITY_BEGIN();
  RUN_TEST(getClientID);
  RUN_TEST(getOutputTopic);
  RUN_TEST(getInputTopic);
  RUN_TEST(getIntegerPayload);
  RUN_TEST(getNamedTopic);
  RUN_TEST(getJSONPayload);
  RUN_TEST(getLastWill);
  RUN_TEST(getFirstWill);
  RUN_TEST(getFloatPayload);
  RUN_TEST(validateCommandJSONReturnsEmptyStringIfValid);
  RUN_TEST(validateCommandJSONReturnsFailureIfRequestIDIsMissing);
  RUN_TEST(validateCommandJSONReturnsFailureIfRequestIDIsNotALong);
  RUN_TEST(validateCommandJSONReturnsFailureIfClientIDIsMissing);
  RUN_TEST(validateCommandJSONReturnsFailureIfClientIDIsNotAString);
  RUN_TEST(validateCommandJSONReturnsFailureIfDataIsMissing);
  RUN_TEST(validateCommandJSONReturnsFailureIfDataIsNoJSON);
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
