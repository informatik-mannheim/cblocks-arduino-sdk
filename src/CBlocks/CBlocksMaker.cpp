#include "CBlocksMaker.h"
#include "CBlocks.h"
#include "Network.h"
#include "Util.h"

CBlocks* makeMQTT(unsigned int objectID, unsigned int instanceID, MQTT mqtt){
  String clientID = Util::getClientID(objectID, instanceID);
  Will firstWill = Util::getFirstWillFor(objectID, instanceID);
  Will lastWill = Util::getLastWillFor(objectID, instanceID);
  Network* network = new Network(clientID, mqtt, firstWill, lastWill);

  return new CBlocks(objectID, instanceID, network);
}
