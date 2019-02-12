#include "CBlocks.h"
#include "CBlocksMaker.h"

#define BAUD_RATE 115200
#define OBJECT_ID 3302
#define INSTANCE_ID 0
#define BUTTON_PIN 21
#define UPDATE_INTERVAL_MS 500

CBlocks::CBlocks* cblocks;
unsigned long lastMillis;

void initCBlocks(){
  cblocks = CBlocks::CBlocksMaker::make(OBJECT_ID, INSTANCE_ID);
  cblocks->begin();
}

void initSensor(){
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void setup(){
  initCBlocks();
  initSensor();

  lastMillis = millis();
}

void loop(){
  if(millis() - lastMillis > UPDATE_INTERVAL_MS){
    cblocks->heartBeat();
    cblocks->updateResource(0, String(digitalRead(BUTTON_PIN)));

    lastMillis = millis();
  }
}
