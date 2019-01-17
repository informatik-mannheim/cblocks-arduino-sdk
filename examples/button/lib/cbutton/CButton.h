#ifndef CBLOCKS_BUTTON_H
#define CBLOCKS_BUTTON_H

#define STATE_RESOURCE 0
#define EVENT_RESOURCE 1

#include "Arduino.h"
#include "CBlocks.h"
#include "JC_Button.h"

namespace CBlocks {

  class CButton {
  private:
    int buttonPin;
    bool isOn;
    bool hasPublished;
    Button* button;
    CBlocks* cblocks;

  public:
    CButton(int buttonPin, CBlocks* cblocks);
    void begin();
    void publishStatus();
  };

  CButton::CButton(int buttonPin, CBlocks* cblocks) :
    buttonPin(buttonPin),
    cblocks(cblocks) {};

  void CButton::begin(){
    button = new Button(buttonPin);
    button->begin();
  }

  void CButton::publishStatus(){
    button->read();

    if(!hasPublished){
      isOn = false;
      cblocks->updateResource(STATE_RESOURCE, "Off");

      hasPublished = true;
    }

    if(button->wasPressed()){
      isOn = !isOn;

      if(isOn){
        cblocks->updateResource(STATE_RESOURCE, "On");
      }else {
        cblocks->updateResource(STATE_RESOURCE, "Off");
      }

      cblocks->updateResource(EVENT_RESOURCE, "pressed");
    }

    if(button->wasReleased()){
      cblocks->updateResource(EVENT_RESOURCE, "released");
    }
  }
}

#endif
