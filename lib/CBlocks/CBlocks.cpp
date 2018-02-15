#include "CBlocks.h"
#include "Util.h"

CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, PubSubClient* mqttClient){
  this->objectID = objectID;
  this->instanceID = instanceID;
  this->mqttClient = mqttClient;
}

void CBlocks::updateResource(unsigned int resourceID, unsigned int value){
}

String CBlocks::getOutputTopicFor(unsigned int resourceID){
  Util::getOutputTopic(objectID, instanceID, resourceID);
}
