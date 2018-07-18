#ifndef CBLOCKS_H
#define CBLOCKS_H

#include "Arduino.h"
#include "Network.h"
#include "Command.h"
#include "PowerManager.h"
#include "UpdateTimer.h"
#include "Pairing.h"
#include "StatusLED.h"

#define BATTERY_STATUS_RESOURCE_ID 255
#define BATTERY_STATUS_UPDATE_INTERVAL_MS 5000

namespace CBlocks{
  enum State { CONNECTION_FAILED, CONNECTED, PAIRING, PAIRED };

  class CBlocks
  {
  private:
    unsigned int objectID;
    unsigned int instanceID;
    Network* network;
    PowerManager* powerManager;
    UpdateTimer* batteryStatusUpdateTimer;
    Pairing* pairing;
    StatusLED* statusLED;
    State state;

    void publishBatteryStatus();
    String getOutputTopicFor(unsigned int resourceID);
    String getInputTopicFor(unsigned int resourceID);
    bool shouldTurnOff();
  public:
    CBlocks(unsigned int objectID, unsigned int instanceID, Network* network, PowerManager* powerManager, Pairing* pairing, StatusLED* statusLED);

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
