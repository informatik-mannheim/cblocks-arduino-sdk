#ifndef UTIL_H
#define UTIL_H

#include "Arduino.h"
#include "ArduinoJson.h"
#include "Will.h"

namespace CBlocks{
  class Util{
  public:
    static String getClientID(unsigned int objectID, unsigned instanceID);
    static String getOutputTopic(unsigned int objectID, unsigned instanceID, int resourceID);
    static String getInputTopic(unsigned int objectID, unsigned instanceID, int resourceID);
    static String getNamedTopic(unsigned int objectID, unsigned instanceID, String resourceName);
    static String getPayloadFor(unsigned int value);
    static String getPayloadFor(float value);
    static String getPayloadFor(JsonObject& data);
    static Will getLastWillFor(unsigned int objectID, unsigned instanceID);
    static Will getFirstWillFor(unsigned int objectID, unsigned instanceID);
    static JsonObject& getJSONForPayload(byte *payload, unsigned int length, DynamicJsonBuffer& buffer);
    static String validateCommandRequestID(JsonObject& json);
    static String validateCommandData(JsonObject& json);
    static String getClientIDFromCommandTopic(String topic);
    static String removeClientIDFromCommandTopic(String topic);
    static String getResponseTopic(String clientID);
  };
}

#endif
