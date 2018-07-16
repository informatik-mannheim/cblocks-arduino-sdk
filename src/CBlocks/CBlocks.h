#ifndef CBLOCKS_H
#define CBLOCKS_H

#include "Arduino.h"
#include "Network.h"
#include "Command.h"
#include "PowerManager.h"

namespace CBlocks{
  class CBlocks
  {
  private:
    unsigned int objectID;
    unsigned int instanceID;
    Network* network;
    PowerManager* powerManager;

    String getOutputTopicFor(unsigned int resourceID);
    String getInputTopicFor(unsigned int resourceID);
  public:
    CBlocks(unsigned int objectID, unsigned int instanceID, Network* network, PowerManager* powerManager);

    void begin();
    void heartBeat();
    void updateResource(unsigned int resourceID, String value);
    void updateResource(unsigned int resourceID, unsigned int value);
    void updateResource(unsigned int resourceID, float value);
    void updateResource(unsigned int resourceID, bool value);
    void updateResource(unsigned int resourceID, JsonObject& json);
    void registerCommand(unsigned int resourceID, commandCallback cb);
  };
}

#endif
