#include "Arduino.h"
#include "Util.h"
#include "SimpleList.h"
#include "unity_arduino.h"
#include "unity.h"
#include "tests.h"
#include "Command.h"

#define BAUD_RATE 115200

void getClientID(){
  TEST_ASSERT_EQUAL_STRING("3303-0", Util::getClientID(3303,0).c_str());
}

void getOutputTopic() {
  TEST_ASSERT_EQUAL_STRING("3303/0/1/output", Util::getOutputTopic(3303, 0, 1).c_str());
}

void getInputTopic() {
  TEST_ASSERT_EQUAL_STRING("+/3303/0/1/input", Util::getInputTopic(3303, 0, 1).c_str());
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

void getJSONForPayload(){
  DynamicJsonBuffer jsonBuffer;

  char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.75608,2.302038]}";
  int length = sizeof(json) / sizeof(json[0]);

  JsonObject& jsonObject = Util::getJSONForPayload((byte*)json, length, jsonBuffer);
  TEST_ASSERT_EQUAL_STRING("gps", jsonObject["sensor"]);
  TEST_ASSERT_EQUAL(1351824120, jsonObject["time"]);
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

void validateCommandRequestIDEmptyStringIfValid(){
  DynamicJsonBuffer buffer;

  JsonObject& json = buffer.createObject();
  json["requestID"] = 4711;

  TEST_ASSERT_EQUAL_STRING("", Util::validateCommandRequestID(json).c_str());
}

void validateCommandRequestIDReturnsErrorIfNotPresent(){
  DynamicJsonBuffer buffer;

  JsonObject& json = buffer.createObject();

  TEST_ASSERT_EQUAL_STRING("Command has no \"requestID\".", Util::validateCommandRequestID(json).c_str());
}

void validateCommandRequestIDReturnsErrorIfString(){
  DynamicJsonBuffer buffer;

  JsonObject& json = buffer.createObject();
  json["requestID"] = "test";

  TEST_ASSERT_EQUAL_STRING("\"requestID\" must be of type long.", Util::validateCommandRequestID(json).c_str());
}

void validateCommandDataEmptyStringIfValid(){
  DynamicJsonBuffer buffer;

  JsonObject& json = buffer.createObject();
  JsonObject& data = json.createNestedObject("data");
  data["value"] = 1234;

  TEST_ASSERT_EQUAL_STRING("", Util::validateCommandData(json).c_str());
}

void validateCommandDataErrorIfNotPresent(){
  DynamicJsonBuffer buffer;

  JsonObject& json = buffer.createObject();

  TEST_ASSERT_EQUAL_STRING("Command has no \"data\".", Util::validateCommandData(json).c_str());
}

void getResponseTopic(){
  TEST_ASSERT_EQUAL_STRING("mqttFX/responses", Util::getResponseTopic(String("mqttFX")).c_str());
}

void getClientIDFromCommandTopic(){
  TEST_ASSERT_EQUAL_STRING("mqttFX", Util::getClientIDFromCommandTopic(String("mqttFX/3303/0/0/input")).c_str());
}

void removeClientIDFromCommandTopic(){
  TEST_ASSERT_EQUAL_STRING("+/3303/0/0/input", Util::removeClientIDFromCommandTopic(String("mqttFX/3303/0/0/input")).c_str());
}

void commandResponseToJSON(){
  DynamicJsonBuffer buffer;
  CommandResponse response;

  response.success = true;
  response.message = "Fail.";
  response.requestID = 4177;

  TEST_ASSERT_EQUAL_STRING("{\"requestID\":4177,\"success\":true,\"message\":\"Fail.\"}", response.toJSON(buffer).c_str());
}

void run_tests(){
  UNITY_BEGIN();
  RUN_TEST(getClientID);
  RUN_TEST(getOutputTopic);
  RUN_TEST(getInputTopic);
  RUN_TEST(getIntegerPayload);
  RUN_TEST(getNamedTopic);
  RUN_TEST(getJSONPayload);
  RUN_TEST(getJSONForPayload);
  RUN_TEST(getLastWill);
  RUN_TEST(getFirstWill);
  RUN_TEST(getFloatPayload);
  RUN_TEST(validateCommandRequestIDEmptyStringIfValid);
  RUN_TEST(validateCommandRequestIDReturnsErrorIfNotPresent);
  RUN_TEST(validateCommandRequestIDReturnsErrorIfString);
  RUN_TEST(validateCommandDataEmptyStringIfValid);
  RUN_TEST(validateCommandDataErrorIfNotPresent);
  RUN_TEST(getResponseTopic);
  RUN_TEST(getClientIDFromCommandTopic);
  RUN_TEST(removeClientIDFromCommandTopic);
  RUN_TEST(commandResponseToJSON);
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
