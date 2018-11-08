#include "Arduino.h"
#include "ESP32PowerManager.h"

namespace CBlocks{
  ESP32PowerManager::ESP32PowerManager(int batteryStatusPin)
    : batteryStatusPin(batteryStatusPin),
      batteryVoltage(4.7) {};

  void ESP32PowerManager::begin(){
    pinMode(batteryStatusPin, INPUT);
  }

  void ESP32PowerManager::readBatteryVoltage(){
    batteryVoltage = analogRead(batteryStatusPin) * (3.3f / 4096) * 2;
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
}
