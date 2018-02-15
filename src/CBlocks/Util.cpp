#include "Arduino.h"
#include "Util.h"

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

String Util::getPayloadFor(unsigned int value){
  return String(value);
}
