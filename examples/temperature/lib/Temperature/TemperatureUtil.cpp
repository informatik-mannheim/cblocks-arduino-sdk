#include "Arduino.h"
#include "TemperatureUtil.h"

unsigned int TemperatureUtil::readMilliVolts(unsigned int analogValue, unsigned int maxAnalogMilliVolts, unsigned int adcResolution){
  float milliVoltsPerAnalogValue = float(maxAnalogMilliVolts) / float(adcResolution);
  return analogValue * milliVoltsPerAnalogValue;
}

float TemperatureUtil::computeTemperature(unsigned int readingMilliVolts, int slope, int offset){
  return (readingMilliVolts / float(slope)) + offset;
}
