#include "Arduino.h"
#include "CBlocks.h"
#include "TemperatureUtil.h"
#include "unity_arduino.h"
#include "unity.h"

#define BAUD_RATE 115200

void calculateTemperatureReturns25ForTmp36(){
  TEST_ASSERT_EQUAL(25.0f, TemperatureUtil::computeTemperature(750, 10, -50));
}

void calculateTemperatureForTmp36WithVoltageDivider(){
  TEST_ASSERT_EQUAL(25.0f, TemperatureUtil::computeTemperature(375, 5, -50));
  TEST_ASSERT_EQUAL(24.0f, TemperatureUtil::computeTemperature(370, 5, -50));
  TEST_ASSERT_EQUAL(0.0f, TemperatureUtil::computeTemperature(250, 5, -50));
}

void readMilliVolts(){
  TEST_ASSERT_EQUAL(375, TemperatureUtil::readMilliVolts(384, 1000, 1024));
}

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void run_tests(){
  UNITY_BEGIN();
  RUN_TEST(calculateTemperatureReturns25ForTmp36);
  RUN_TEST(calculateTemperatureForTmp36WithVoltageDivider);
  RUN_TEST(readMilliVolts);
  UNITY_END();
}

void setup(){
  initAndWaitForSerial();
  run_tests();
}

void loop(){
}
