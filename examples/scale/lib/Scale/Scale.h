#ifndef SCALE_H
#define SCALE_H

#include "Arduino.h"
#include "CBlocks.h"
#include "Command.h"
#include "UpdateTimer.h"
#include "HX711.h"

#define WEIGHT_RESOURCE_ID 0
#define UPDATE_INTERVAL_IN_MS 1000

namespace CBlocks{
  class Scale{
  private:
    long calibrationFactor;

    HX711* scale;
    CBlocks* cblocks;
    UpdateTimer* updateTimer;
  public:
    Scale(HX711* scale, long calibrationFactor, CBlocks* cblocks);
    void begin();
    void publishStatus();
  };

  Scale::Scale(HX711* scale, long calibrationFactor, CBlocks* cblocks){
    this->scale = scale;
    this->calibrationFactor = calibrationFactor;
    this->cblocks = cblocks;
  }

  void Scale::begin(){
    this->scale->set_scale(calibrationFactor);
    this->scale->tare();
    this->updateTimer = new UpdateTimer(UPDATE_INTERVAL_IN_MS);
  }

  void Scale::publishStatus(){
    cblocks->heartBeat();

    if(updateTimer->updateIntervalExceeded()){
      float val = scale->get_units(10);
      cblocks->updateResource(WEIGHT_RESOURCE_ID, val);
    }
  }
}

#endif
