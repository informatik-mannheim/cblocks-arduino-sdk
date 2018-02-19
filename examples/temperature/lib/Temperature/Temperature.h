#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Arduino.h"
#include "CBlocks.h"

#define MAX_ANALOG_MILLI_VOLTS 1000
#define ADC_RESOLUTION  1024
#define TEMPERATURE_RESOURCE_ID 0
#define SLOPE 5
#define OFFSET (-50)
#define TEMPERATURE_RESOURCE_ID 0

class Temperature{
private:
  int analogPin;
  unsigned int readingMilliVolts;
  unsigned int analogValue;
  float temperatureInCelsius;
  CBlocks* cblocks;

  void initPins();
  void readMilliVolts();
  void computeTemperature();
  void publishTemperature();

public:
  Temperature(int analogPin, CBlocks* cblocks);

  void begin();
  void update();
};

#endif
