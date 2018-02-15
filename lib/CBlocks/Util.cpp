#include "Arduino.h"
#include "Util.h"

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
