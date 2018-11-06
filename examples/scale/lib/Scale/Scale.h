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
    int tarePin;
    static volatile byte buttonPressed;

    static void tareInterruptHandler();
  public:
    Scale(HX711* scale, long calibrationFactor, CBlocks* cblocks, int tarePin);
    void begin();
    void publishStatus();
  };

  volatile byte Scale::buttonPressed = false;

  Scale::Scale(HX711* scale, long calibrationFactor, CBlocks* cblocks, int tarePin){
    this->scale = scale;
    this->calibrationFactor = calibrationFactor;
    this->cblocks = cblocks;
    this->tarePin = tarePin;
  }

  void Scale::begin(){
    this->scale->set_scale(calibrationFactor);
    this->scale->tare();
    this->updateTimer = new UpdateTimer(UPDATE_INTERVAL_IN_MS);

    pinMode(this->tarePin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(this->tarePin), tareInterruptHandler, FALLING);
  }

  void Scale::tareInterruptHandler(){
    buttonPressed = true;
  }

  void Scale::publishStatus(){
    cblocks->heartBeat();

    if(buttonPressed){
      this->scale->tare();
      Serial.println("Tare");
      buttonPressed = false;
    }

    if(updateTimer->updateIntervalExceeded()){
      float val = scale->get_units();
      cblocks->updateResource(WEIGHT_RESOURCE_ID, val);
      Serial.println(val);
    }
  }
}

#endif
