#include "CBlocksMaker.h"
#include "CBlocks.h"
#include "Network.h"
#include "Util.h"

CBlocks* makeMQTT(unsigned int objectID, unsigned int instanceID, MQTT mqtt){
  Network* network = new Network(Util::getClientID(objectID, instanceID), mqtt, Util::getFirstWillFor(objectID, instanceID), Util::getLastWillFor(objectID, instanceID));

  return new CBlocks(objectID, instanceID, network);
}
