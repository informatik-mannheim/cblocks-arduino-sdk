#include "CBlocks.h"
#include "Util.h"

CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, PubSubClient* mqttClient){
  this->objectID = objectID;
  this->instanceID = instanceID;
  this->mqttClient = mqttClient;
}

void CBlocks::updateResource(unsigned int resourceID, unsigned int value){
}

const char* CBlocks::getOutputTopicFor(unsigned int resourceID){
  return Util::getOutputTopic(objectID, instanceID, resourceID);
}
