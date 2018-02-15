#include "Arduino.h"
#include "Util.h"

const char* Util::getOutputTopic(unsigned int objectID, unsigned instanceID, int resourceID){
  char topic[100];

  snprintf(topic, 100, "%u/%u/%u/output", objectID, instanceID, resourceID);

  // create a new buffer with size of string
  char result[strlen(topic)];
  memcpy(result, topic, strlen(topic));

  return result;
}
