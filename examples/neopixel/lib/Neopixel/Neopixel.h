#ifndef LED
#define LED

#include "Arduino.h"
#include "CBlocks.h"
#include "Command.h"
#include "Color.h"
#include "UpdateTimer.h"
#include <Adafruit_NeoPixel.h>

#define IS_ON_RESOURCE_ID 0
#define COLOR_RESOURCE_ID 1
#define UPDATE_INTERVAL_IN_MS 1000
#define PIXEL_OFFSET 1

namespace CBlocks{
  class Neopixel{
  private:
    static bool isOn;
    static Color* color;

    static int numberOfPixels;
    static Adafruit_NeoPixel* strip;
    CBlocks* cblocks;
    UpdateTimer* updateTimer;

    static void renderPixels();
    static void renderPixelsWithColor();
    static void switchPixelsOff();
  public:
    Neopixel(Adafruit_NeoPixel* strip, CBlocks* cblocks, int numberOfPixels);
    void begin();
    void publishStatus();

    static CommandResponse isOnCommandCallback(JsonObject& json);
    static CommandResponse colorCommandCallback(JsonObject& json);
  };

  bool Neopixel::isOn = true;
  Color* Neopixel::color = new Color(50,50,50);
  Adafruit_NeoPixel* Neopixel::strip = {0};
  int Neopixel::numberOfPixels = 0;

  Neopixel::Neopixel(Adafruit_NeoPixel* strip, CBlocks* cblocks, int numberOfPixels){
    this->strip = strip;
    this->cblocks = cblocks;
    this->numberOfPixels = numberOfPixels;
    this->updateTimer = new UpdateTimer(UPDATE_INTERVAL_IN_MS);
  }

  void Neopixel::begin(){
    renderPixels();
    cblocks->registerCommand(IS_ON_RESOURCE_ID, isOnCommandCallback);
    cblocks->registerCommand(COLOR_RESOURCE_ID, colorCommandCallback);
  }

  void Neopixel::publishStatus(){
    cblocks->heartBeat();

    if(updateTimer->updateIntervalExceeded()){
      cblocks->updateResource(IS_ON_RESOURCE_ID, isOn);
      cblocks->updateResource(COLOR_RESOURCE_ID, color->toJson());
    }
  }

  CommandResponse Neopixel::isOnCommandCallback(JsonObject &json){
    isOn = json["data"];
    renderPixels();

    return CommandResponse::getSuccessCommandResponseFor(json["requestID"]);
  }

  void Neopixel::renderPixels(){
    if(isOn)
      renderPixelsWithColor();
    else
      switchPixelsOff();

    strip->show();
  }

  void Neopixel::renderPixelsWithColor(){
    for(int i=PIXEL_OFFSET;i<numberOfPixels+PIXEL_OFFSET;i++){
      strip->setPixelColor(i, strip->Color(color->green, color->red, color->blue));
    }
  }

  void Neopixel::switchPixelsOff(){
    for(int i=PIXEL_OFFSET;i<numberOfPixels+PIXEL_OFFSET;i++){
      strip->setPixelColor(i, strip->Color(0, 0, 0));
    }
  }

  CommandResponse Neopixel::colorCommandCallback(JsonObject &json){
    JsonObject& data = json["data"];

    color->importJson(data);
    renderPixels();

    return CommandResponse::getSuccessCommandResponseFor(json["requestID"]);
  }
}

#endif
