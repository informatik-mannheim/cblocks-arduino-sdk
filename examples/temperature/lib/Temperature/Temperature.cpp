#include "Arduino.h"
#include "Temperature.h"
#include "TemperatureUtil.h"
#include "UpdateTimer.h"

Temperature::Temperature(int analogPin, CBlocks* cblocks){
  this->analogPin = analogPin;
  this->cblocks = cblocks;
  this->updateTimer = new UpdateTimer(UPDATE_INTERVAL_IN_MS);
}

void Temperature::begin(){
  initPins();
}

void Temperature::initPins(){
  pinMode(analogPin, INPUT);
}

void Temperature::update(){
  readMilliVolts();
  computeTemperature();
  publishTemperature();
}

void Temperature::readMilliVolts(){
  unsigned int analogValue = analogRead(analogPin);

  readingMilliVolts = TemperatureUtil::readMilliVolts(analogValue, MAX_ANALOG_MILLI_VOLTS, ADC_RESOLUTION);
}

void Temperature::computeTemperature(){
  temperatureInCelsius = TemperatureUtil::computeTemperature(readingMilliVolts, SLOPE, OFFSET);
}

void Temperature::publishTemperature(){
  cblocks->updateResource(TEMPERATURE_RESOURCE_ID, temperatureInCelsius);
}
