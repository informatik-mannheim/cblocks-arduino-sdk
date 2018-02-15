#include "Arduino.h"
#include <PubSubClient.h>

#ifndef CBLOCKS_H
#define CBLOCKS_H

class CBlocks
{
private:
  unsigned int objectID;
  unsigned int instanceID;
  PubSubClient* mqttClient;
  
  String getOutputTopicFor(unsigned int resourceID);

public:
  CBlocks(unsigned int objectID, unsigned int instanceID, PubSubClient* mqttClient);

  void updateResource(unsigned int resourceID, unsigned int value);
};

#endif
