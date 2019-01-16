#ifndef ESP32_POWER_MANAGER
#define ESP32_POWER_MANAGER

#include "Network.h"
#include "PowerManager.h"
#include "Arduino.h"

#define BATTERY_SHUT_DOWN_THRESHOLD_V 3.3
#define BATTERY_HIGH_THRESHOLD 3.6
#define BATTERY_MEDIUM_THRESHOLD 3.4

namespace CBlocks{
  class ESP32PowerManager : public PowerManager {
  private:
    static int enablePin;
    int shutDownPin;
    int batteryStatusPin;
    float batteryVoltage;
    static Network* network;

    void readBatteryVoltage();
    static void handleShutDownInterrupt();
  public:
    ESP32PowerManager(int enablePin, int shutDownPin, int batteryStatusPin);
    virtual void begin();
    virtual bool isBatteryLow();
    virtual void turnOff();
    virtual void turnOn();
    virtual BatteryStatus getBatteryStatus();
    virtual void setNetwork(Network* network);
  };
}

#endif
