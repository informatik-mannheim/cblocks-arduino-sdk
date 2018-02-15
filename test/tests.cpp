#include "Arduino.h"
#include "Util.h"
#include "unity_arduino.h"
#include "unity.h"
#include "tests.h"

void getOutputTopic() {
    TEST_ASSERT_EQUAL_STRING("3303/0/1/output", Util::getOutputTopic(3303, 0, 1));
}

void getInputTopic() {
    TEST_ASSERT_EQUAL_STRING("3303/0/1/input", Util::getInputTopic(3303, 0, 1));
}

void run_tests(){
  UNITY_BEGIN();
  RUN_TEST(getOutputTopic);
  RUN_TEST(getInputTopic);
  UNITY_END();
}
