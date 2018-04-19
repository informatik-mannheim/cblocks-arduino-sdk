#include "UpdateTimer.h"
#include "Arduino.h"

namespace CBlocks{
  UpdateTimer::UpdateTimer(long updateIntervalInMS){
    this->updateIntervalInMS = updateIntervalInMS;
  }

  bool UpdateTimer::updateIntervalExceeded(){
    if(millis() - this->lastUpdateInMS > updateIntervalInMS){
      this->lastUpdateInMS = millis();
      return true;
    }

    return false;
  }
}
