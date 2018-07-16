#ifndef ESP32_POWER_MANAGER
#define ESP32_POWER_MANAGER

#include "PowerManager.h"
#include "Arduino.h"

namespace CBlocks{
  class ESP32PowerManager : public PowerManager {
  private:
    int powerPin;
    gpio_num_t wakeUpPin;
    int pixelPin;

    void turnPowerOff();

  public:
    ESP32PowerManager(int powerPin, gpio_num_t wakeUpPin, int pixelPin);
    virtual void begin();
    virtual bool isPowerButtonOn();
    virtual void turnOff();
    virtual void turnOn();
  };
}

#endif
