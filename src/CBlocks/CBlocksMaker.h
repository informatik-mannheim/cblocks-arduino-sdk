#ifndef CBLOCKS_MAKER_H
#define CBLOCKS_MAKER_H

#include "CBlocks.h"
#include "Network.h"

CBlocks* makeMQTT(unsigned int objectID, unsigned int instanceID, MQTT mqtt);

#endif
