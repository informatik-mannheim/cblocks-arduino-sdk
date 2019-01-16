#include "Network.h"
#include "Arduino.h"
#include "ESP32PowerManager.h"

namespace CBlocks{
  int ESP32PowerManager::enablePin = 0;
  Network* ESP32PowerManager::network = NULL;

  ESP32PowerManager::ESP32PowerManager(int enablePin, int shutDownPin, int batteryStatusPin)
    : shutDownPin(shutDownPin),
      batteryStatusPin(batteryStatusPin),
      batteryVoltage(4.7) {
        this->enablePin = enablePin;
      };

  void ESP32PowerManager::begin(){
    pinMode(enablePin, OUTPUT);
    pinMode(shutDownPin, INPUT_PULLUP);
    pinMode(batteryStatusPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(shutDownPin), handleShutDownInterrupt, FALLING);

    turnOn();
  }

  void ESP32PowerManager::turnOn(){
    digitalWrite(enablePin, HIGH);
  }

  bool ESP32PowerManager::isBatteryLow(){
    readBatteryVoltage();

    return batteryVoltage < BATTERY_SHUT_DOWN_THRESHOLD_V;
  }

  void ESP32PowerManager::readBatteryVoltage(){
    batteryVoltage = analogRead(batteryStatusPin) * (3.3f / 4096) * 2;
  }

  void ESP32PowerManager::turnOff(){
    handleShutDownInterrupt();
  }

  BatteryStatus ESP32PowerManager::getBatteryStatus(){
    readBatteryVoltage();

    if(batteryVoltage > BATTERY_HIGH_THRESHOLD){
      return high;
    }else if(batteryVoltage > BATTERY_MEDIUM_THRESHOLD){
      return medium;
    }

    return low;
  }

  void ESP32PowerManager::setNetwork(Network* n){
    network = n;
  }

  void ESP32PowerManager::handleShutDownInterrupt(){
    network->disconnect();
    digitalWrite(enablePin, HIGH);
  };
}
