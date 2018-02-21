#include "Command.h"
#include "Arduino.h"
#include "ArduinoJson.h"

String CommandResponse::toJSON(DynamicJsonBuffer& buffer){
  JsonObject& o = buffer.createObject();

  o["requestID"] = requestID;
  o["success"] = success;
  o["message"] = message;

  String result;

  o.printTo(result);

  return result;
}
