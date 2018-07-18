#include "Command.h"
#include "Arduino.h"
#include "ArduinoJson.h"

namespace CBlocks{
  String CommandResponse::toJSON(DynamicJsonBuffer& buffer){
    JsonObject& o = buffer.createObject();

    o["requestID"] = requestID;
    o["success"] = success;
    o["message"] = message;

    String result;

    o.printTo(result);

    return result;
  }

  CommandResponse CommandResponse::getSuccessCommandResponseFor(unsigned int requestID){
    CommandResponse r = {requestID, true, ""};

    return r;
  }

  CommandResponse CommandResponse::getErrorCommandResponseFor(unsigned int requestID, String message){
    CommandResponse r = {requestID, false, message};

    return r;
  }
}
