#ifndef LED
#define LED

#include "Arduino.h"
#include "CBlocks.h"
#include "Command.h"
#include "Color.h"
#include <Adafruit_NeoPixel.h>

#define IS_ON_RESOURCE_ID 0
#define COLOR_RESOURCE_ID 1

namespace CBlocks{
  class Neopixel{
  private:
    static bool isOn;
    static Color* color;

    static Adafruit_NeoPixel* strip;
    CBlocks* cblocks;

    static void renderPixels();
    static void renderPixelsWithColor();
    static void switchPixelsOff();
  public:
    Neopixel(Adafruit_NeoPixel* strip, CBlocks* cblocks);
    void begin();
    void publishStatus();

    static CommandResponse isOnCommandCallback(JsonObject& json);
    static CommandResponse colorCommandCallback(JsonObject& json);
  };

  bool Neopixel::isOn = true;
  Color* Neopixel::color = new Color(125,125,125);
  Adafruit_NeoPixel* Neopixel::strip = {0};

  Neopixel::Neopixel(Adafruit_NeoPixel* strip, CBlocks* cblocks){
    this->strip = strip;
    this->cblocks = cblocks;
  }

  void Neopixel::begin(){
    strip->begin();
    renderPixels();
    cblocks->registerCommand(IS_ON_RESOURCE_ID, isOnCommandCallback);
    cblocks->registerCommand(COLOR_RESOURCE_ID, colorCommandCallback);
  }

  void Neopixel::publishStatus(){
    cblocks->heartBeat();
    cblocks->updateResource(IS_ON_RESOURCE_ID, isOn);
    cblocks->updateResource(COLOR_RESOURCE_ID, color->toJson());
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
    for(int i=0;i<strip->numPixels();i++){
      strip->setPixelColor(i, strip->Color(color->red, color->green, color->blue));
    }
  }

  void Neopixel::switchPixelsOff(){
    for(int i=0;i<strip->numPixels();i++){
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
