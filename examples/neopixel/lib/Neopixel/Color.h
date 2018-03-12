#ifndef COLOR
#define COLOR

#include "ArduinoJson.h"

namespace Neopixel{
  class Color{
  private:
    StaticJsonBuffer<100> buffer;
    JsonObject* json;
  public:
    Color(uint8_t red, uint8_t green, uint8_t blue);
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    JsonObject& toJson();
    void importJson(JsonObject& json);
  };

  Color::Color(uint8_t red, uint8_t green, uint8_t blue){
    this->red = red;
    this->green = green;
    this->blue = blue;

    json = &(buffer.createObject());
  }

  JsonObject& Color::toJson(){
    json->set("red", red);
    json->set("green", green);
    json->set("blue", blue);

    return *json;
  }

  void Color::importJson(JsonObject &json){
    this->red = json["red"];
    this->green = json["green"];
    this->blue = json["blue"];
  }
}

#endif
