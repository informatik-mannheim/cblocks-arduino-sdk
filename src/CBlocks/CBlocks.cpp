#include "CBlocks.h"
#include "Util.h"

CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, Network* network){
  this->objectID = objectID;
  this->instanceID = instanceID;
  this->network = network;
}

void CBlocks::begin(){
  network->init();
}

void CBlocks::heartBeat(){
  network->keepOnline();
}

void CBlocks::updateResource(unsigned int resourceID, String value){
  network->publish(getOutputTopicFor(resourceID), value);
}

void CBlocks::updateResource(unsigned int resourceID, unsigned int value){
  network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
}

String CBlocks::getOutputTopicFor(unsigned int resourceID){
  return Util::getOutputTopic(objectID, instanceID, resourceID);
}

void CBlocks::updateResource(unsigned int resourceID, float value){
  network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
}

void CBlocks::updateResource(unsigned int resourceID, bool value){
  updateResource(resourceID, (unsigned int)value);
}

void CBlocks::updateResource(unsigned int resourceID, JsonObject& value){
  network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
}

void CBlocks::registerCommand(unsigned int resourceID, commandCallback cb){
  network->subscribe(getInputTopicFor(resourceID), cb);
}

String CBlocks::getInputTopicFor(unsigned int resourceID){
  return Util::getInputTopic(objectID, instanceID, resourceID);
}
