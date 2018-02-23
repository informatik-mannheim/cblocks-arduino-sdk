#ifndef COLOR
#define COLOR

#include "ArduinoJson.h"

namespace Neopixel{
  class Color{
  private:
    StaticJsonBuffer<100> buffer;
    JsonObject* json;

    static String validateElement(String element, JsonObject &json);
  public:
    Color(uint8_t red, uint8_t green, uint8_t blue);
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    JsonObject& toJson();
    static bool isValidJson(JsonObject& json);
    static String validateJson(JsonObject& json);
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

  bool Color::isValidJson(JsonObject &json){
    return (validateJson(json).length() == 0);
  }

  String Color::validateJson(JsonObject &json){
    if(validateElement("red", json).length() > 0){
      return validateElement("red", json);
    }

    if(validateElement("green", json).length() > 0){
      return validateElement("green", json);
    }

    if(validateElement("blue", json).length() > 0){
      return validateElement("blue", json);
    }

    return String("");
  }

  String Color::validateElement(String element, JsonObject &json){
    String result;

    if(!json.containsKey(element)){
      result = String("Please set element ");
      result.concat(element);
      result.concat(".");

      return result;
    }

    if(!json.is<unsigned int>(element) || json.get<unsigned int>(element) > 255){
      element.concat(" must be a number between 0 and 255.");
      return element;
    }

    return result;
  }
}

#endif
