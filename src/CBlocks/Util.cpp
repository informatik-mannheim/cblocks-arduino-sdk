#include "Arduino.h"
#include "Util.h"

const char* Util::getClientID(unsigned int objectID, unsigned int instanceID){
  char clientID[20];

  snprintf(clientID, 20, "%u-%u", objectID, instanceID);

  return clientID;
}

const char* Util::getOutputTopic(unsigned int objectID, unsigned instanceID, int resourceID){
  char topic[100];

  snprintf(topic, 100, "%u/%u/%u/output", objectID, instanceID, resourceID);

  return topic;
}

const char* Util::getInputTopic(unsigned int objectID, unsigned instanceID, int resourceID){
  char topic[100];

  snprintf(topic, 100, "%u/%u/%u/input", objectID, instanceID, resourceID);

  return topic;
}
