#ifndef CBLOCKS_MAKER_H
#define CBLOCKS_MAKER_H

#include "CBlocks.h"
#include "StatusLED.h"
#include "Link.h"
#include "PowerManager.h"

namespace CBlocks{
  CBlocks* makeMQTT(unsigned int objectID, unsigned int instanceID, Link* link, MQTT mqtt, StatusLED* statusLED, PowerManager* powerManager);
}

#endif
