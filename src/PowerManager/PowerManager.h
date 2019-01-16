#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

namespace CBlocks{
  enum BatteryStatus { low, medium, high };

  class PowerManager{
  public:
    virtual void begin();
    virtual bool isBatteryLow();
    virtual void turnOff();
    virtual BatteryStatus getBatteryStatus();
    virtual void setNetwork(Network* network);
  };
}

#endif
