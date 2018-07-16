#include "Arduino.h"
#include "ESP32PowerManager.h"

namespace CBlocks{
  ESP32PowerManager::ESP32PowerManager(int powerPin, gpio_num_t wakeUpPin, int pixelPin)
    : powerPin(powerPin),
      wakeUpPin(wakeUpPin),
      pixelPin(pixelPin) {};

  void ESP32PowerManager::begin(){
    pinMode(powerPin, OUTPUT);
    pinMode(wakeUpPin, INPUT_PULLUP);

    esp_sleep_enable_ext0_wakeup(wakeUpPin, LOW);
    turnOn();
  }

  bool ESP32PowerManager::isPowerButtonOn(){
    return !digitalRead(wakeUpPin);
  }

  void ESP32PowerManager::turnOff(){
    turnPowerOff();
    esp_deep_sleep_start();
  }

  void ESP32PowerManager::turnPowerOff(){
    digitalWrite(powerPin, LOW);
    digitalWrite(pixelPin, HIGH); // this makes the status leds turn off
  }

  void ESP32PowerManager::turnOn(){
    digitalWrite(powerPin, HIGH);
  }
}
