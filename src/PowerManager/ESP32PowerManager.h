#ifndef ESP32_POWER_MANAGER
#define ESP32_POWER_MANAGER

#include "PowerManager.h"
#include "Arduino.h"

#define BATTERY_SHUT_DOWN_THRESHOLD_V 3.3
#define BATTERY_HIGH_THRESHOLD 3.6
#define BATTERY_MEDIUM_THRESHOLD 3.4

namespace CBlocks{
  class ESP32PowerManager : public PowerManager {
  private:
    int batteryStatusPin;
    float batteryVoltage;

    void turnPowerOff();
    void readBatteryVoltage();
  public:
    ESP32PowerManager(int batteryStatusPin);
    virtual void begin();
    virtual BatteryStatus getBatteryStatus();
  };
}

#endif
