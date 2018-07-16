#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

namespace CBlocks{
  class PowerManager{
  public:
    virtual void begin();
    virtual bool isPowerButtonOn();
    virtual void turnOff();
    virtual void turnOn();
  };
}

#endif
