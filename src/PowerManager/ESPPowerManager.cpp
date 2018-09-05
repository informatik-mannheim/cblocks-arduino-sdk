#include "Arduino.h"
#include "ESP32PowerManager.h"

namespace CBlocks{
  ESP32PowerManager::ESP32PowerManager(int powerPin, gpio_num_t wakeUpPin, int pixelPin, int batteryStatusPin)
    : powerPin(powerPin),
      wakeUpPin(wakeUpPin),
      pixelPin(pixelPin),
      batteryStatusPin(batteryStatusPin),
      batteryVoltage(4.7) {};

  void ESP32PowerManager::begin(){
    pinMode(powerPin, OUTPUT);
    pinMode(wakeUpPin, INPUT_PULLUP);
    pinMode(batteryStatusPin, INPUT);

    esp_sleep_enable_ext0_wakeup(wakeUpPin, LOW);
    turnOn();
  }

  void ESP32PowerManager::turnOn(){
    digitalWrite(powerPin, HIGH);
  }

  bool ESP32PowerManager::isPowerButtonOn(){
    return !digitalRead(wakeUpPin);
  }

  bool ESP32PowerManager::isBatteryLow(){
    readBatteryVoltage();

    return batteryVoltage < BATTERY_SHUT_DOWN_THRESHOLD_V;
  }

  void ESP32PowerManager::readBatteryVoltage(){
    batteryVoltage = analogRead(batteryStatusPin) * (3.3f / 4096) * 2;
  }

  void ESP32PowerManager::turnOff(){
    turnPowerOff();
    esp_deep_sleep_start();
  }

  void ESP32PowerManager::turnPowerOff(){
    digitalWrite(powerPin, LOW);
    digitalWrite(pixelPin, HIGH); // this makes the status leds turn off
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
