#ifndef TEMPERATURE_UTIL_H
#define TEMPERATURE_UTIL_H

#include "Arduino.h"

class TemperatureUtil{
public:
  static unsigned int readMilliVolts(unsigned int analogValue, unsigned int maxAnalogMilliVolts, unsigned int adcResolution);
  static float computeTemperature(unsigned int readingMilliVolts, int slope, int offset);
};

#endif
