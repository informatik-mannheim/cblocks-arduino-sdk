#include "Arduino.h"
#include "Util.h"
#include "ArduinoJson.h"

String Util::getClientID(unsigned int objectID, unsigned int instanceID){
  String clientID(objectID);
  clientID.concat("-");
  clientID.concat(instanceID);

  return clientID;
}

String Util::getOutputTopic(unsigned int objectID, unsigned instanceID, int resourceID){
  String topic(objectID);
  topic.concat("/");
  topic.concat(instanceID);
  topic.concat("/");
  topic.concat(resourceID);
  topic.concat("/");
  topic.concat("output");

  return topic;
}

String Util::getInputTopic(unsigned int objectID, unsigned instanceID, int resourceID){
  String topic(objectID);
  topic.concat("/");
  topic.concat(instanceID);
  topic.concat("/");
  topic.concat(resourceID);
  topic.concat("/");
  topic.concat("input");

  return topic;
}

String Util::getNamedTopic(unsigned int objectID, unsigned instanceID, String resourceName){
  String topic(objectID);
  topic.concat("/");
  topic.concat(instanceID);
  topic.concat("/");
  topic.concat(resourceName);

  return topic;
}

String Util::getPayloadFor(unsigned int value){
  return String(value);
}

String Util::getPayloadFor(float value){
  return String(value);
}

String Util::getPayloadFor(JsonObject& data){
  String payload;
  data.printTo(payload);

  return payload;
}

Will Util::getLastWillFor(unsigned int objectID, unsigned int instanceID){
  Will will = {
    Util::getNamedTopic(objectID, instanceID, "status"),
    2,
    true,
    String("offline")
  };

  return will;
}

Will Util::getFirstWillFor(unsigned int objectID, unsigned int instanceID){
  Will will = {
    Util::getNamedTopic(objectID, instanceID, "status"),
    2,
    true,
    String("online")
  };

  return will;
}

// TODO check types
String Util::validateCommandJSON(String json, DynamicJsonBuffer& buffer){
  JsonObject& root = buffer.parseObject(json);

  if(!root.success()){
    return String("Invalid JSON.");
  }

  if(!root.containsKey("requestID")){
    return String("Command has no \"requestID\".");
  }

  if(!root.is<unsigned long>("requestID")){
    return String("\"requestID\" must be of type long.");
  }

  if(!root.containsKey("clientID")){
    return String("Command has no \"clientID\".");
  }

  if(!root.is<const char*>("clientID")){
    return String("\"clientID\" must be of type String.");
  }

  if(!root.containsKey("data")){
    return String("Command has no \"data\".");
  }

  JsonObject& data = buffer.parseObject(root.get<String>("data"));

  if(!data.success()){
    return String("Data is invalid JSON.");
  }

  return String("");
}
