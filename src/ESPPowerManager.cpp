#include "Arduino.h"
#include "ESP32PowerManager.h"

namespace CBlocks{
  volatile bool ESP32PowerManager::isPowerDownPressed = false;

  ESP32PowerManager::ESP32PowerManager(int enablePin, int shutDownPin, int batteryStatusPin)
    : enablePin(enablePin),
      shutDownPin(shutDownPin),
      batteryStatusPin(batteryStatusPin),
      batteryVoltage(4.7) {
        this->enablePin = enablePin;
      };

  void ESP32PowerManager::begin(){
    pinMode(enablePin, OUTPUT);
    pinMode(shutDownPin, INPUT);
    pinMode(batteryStatusPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(shutDownPin), handleShutDownInterrupt, RISING);

    turnOn();
  }

  void ESP32PowerManager::turnOn(){
    digitalWrite(enablePin, HIGH);
  }

  bool ESP32PowerManager::isPowerButtonOn(){
    return !isPowerDownPressed;
  }

  bool ESP32PowerManager::isBatteryLow(){
    return false;
    readBatteryVoltage();

    return batteryVoltage < BATTERY_SHUT_DOWN_THRESHOLD_V;
  }

  void ESP32PowerManager::readBatteryVoltage(){
    batteryVoltage = analogRead(batteryStatusPin) * (3.3f / 4096) * 2;
  }

  void ESP32PowerManager::turnOff(){
    digitalWrite(enablePin, LOW);
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

  void IRAM_ATTR ESP32PowerManager::handleShutDownInterrupt(){
    isPowerDownPressed = true;
  };
}
