#include "CBlocksMaker.h"
#include "CBlocks.h"
#include "Link.h"
#include "WiFiLink.h"
#include "StatusLED.h"
#include "Network.h"
#include "Util.h"
#include "StatusLED.h"
#include "Link.h"

namespace CBlocks{
  CBlocks* makeMQTT(unsigned int objectID, unsigned int instanceID, Link* link, MQTT mqtt, StatusLED* statusLED){
    String clientID = Util::getClientID(objectID, instanceID);
    Will firstWill = Util::getFirstWillFor(objectID, instanceID);
    Will lastWill = Util::getLastWillFor(objectID, instanceID);

    Network* network = new Network(link, statusLED, clientID, mqtt, firstWill, lastWill);

    return new CBlocks(objectID, instanceID, network);
  }
}
