#ifndef CBLOCKS_UPDATE_TIMER_H
#define CBLOCKS_UPDATE_TIMER_H

namespace CBlocks{
  class UpdateTimer{
  private:
    long updateIntervalInMS;
    long lastUpdateInMS;
  public:
    UpdateTimer(long updateIntervalInMS);
    bool updateIntervalExceeded();
  };
}

#endif
