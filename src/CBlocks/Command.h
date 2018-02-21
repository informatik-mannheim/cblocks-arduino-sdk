#ifndef COMMAND_H
#define COMMAND_H

#include "Arduino.h"
#include "ArduinoJson.h"

struct CommandResponse{
  unsigned int requestID;
  bool success;
  String message;
  String toJSON(DynamicJsonBuffer& buffer);
};

typedef CommandResponse (*commandCallback)(JsonObject& json);

#endif
