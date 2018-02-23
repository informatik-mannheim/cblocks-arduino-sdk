#ifndef LED
#define LED

#include "Arduino.h"
#include "CBlocks.h"
#include "Command.h"
#include "Color.h"
#include <Adafruit_NeoPixel.h>

#define IS_ON_RESOURCE_ID 0
#define COLOR_RESOURCE_ID 1

namespace Neopixel{
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
  };

  bool Neopixel::isOn = false;
  Color* Neopixel::color = new Color(0,255,255);
  Adafruit_NeoPixel* Neopixel::strip = {0};

  Neopixel::Neopixel(Adafruit_NeoPixel* strip, CBlocks* cblocks){
    this->strip = strip;
    this->cblocks = cblocks;
  }

  void Neopixel::begin(){
    strip->begin();
    renderPixels();
    cblocks->registerCommand(IS_ON_RESOURCE_ID, isOnCommandCallback);
  }

  void Neopixel::publishStatus(){
    cblocks->updateResource(IS_ON_RESOURCE_ID, isOn);
    cblocks->updateResource(COLOR_RESOURCE_ID, color->toJson());
  }

  CommandResponse Neopixel::isOnCommandCallback(JsonObject &json){
    if(json.is<bool>("data")){
      isOn = json["data"];
      renderPixels();

      return CommandResponse::getSuccessCommandResponseFor(json["requestID"]);
    }

    return CommandResponse::getErrorCommandResponseFor(json["requestID"], "Data must be of type bool.");
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
}

#endif
