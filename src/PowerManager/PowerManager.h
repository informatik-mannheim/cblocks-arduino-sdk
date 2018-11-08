#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

namespace CBlocks{
  enum BatteryStatus { low, medium, high };

  class PowerManager{
  public:
    virtual void begin();
    virtual BatteryStatus getBatteryStatus();
  };
}

#endif
