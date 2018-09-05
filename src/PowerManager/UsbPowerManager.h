#ifndef USB_POWER_MANAGER
#define USB_POWER_MANAGER

#include "PowerManager.h"
#include "Arduino.h"

namespace CBlocks{
  class UsbPowerManager : public PowerManager {
  public:
    UsbPowerManager();
    virtual void begin();
    virtual bool isBatteryLow();
    virtual bool isPowerButtonOn();
    virtual void turnOff();
    virtual void turnOn();
    virtual BatteryStatus getBatteryStatus();
  };
}

#endif
