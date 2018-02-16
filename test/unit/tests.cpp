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
  TEST_ASSERT_EQUAL_STRING("55", Util::getPayloadFor(55).c_str());
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
  Serial.println(payload);
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
