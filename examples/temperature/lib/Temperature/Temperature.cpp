#include "Arduino.h"
#include "Temperature.h"
#include "TemperatureUtil.h"

Temperature::Temperature(int analogPin, unsigned int updateIntervalInMS, CBlocks* cblocks){
  this->analogPin = analogPin;
  this->updateIntervalInMS = updateIntervalInMS;
  this->cblocks = cblocks;
}

void Temperature::begin(){
  initPins();
}

void Temperature::initPins(){
  pinMode(analogPin, INPUT);
}

void Temperature::update(){
  delay(updateIntervalInMS); //TODO wait for millis
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

int Temperature::getComputedTemperature(){
  return temperatureInCelsius;
}
