#ifndef CBLOCKS_H
#define CBLOCKS_H

#include "Arduino.h"
#include "Network.h"
#include "Command.h"
#include "PowerManager.h"
#include "UpdateTimer.h"
#include "Pairing.h"
#include "StatusLED.h"
#include "Fsm.h"

#define BATTERY_STATUS_RESOURCE_ID 255
#define BATTERY_STATUS_UPDATE_INTERVAL_MS 5000

namespace CBlocks{
  enum StateTransition { IS_PAIRED, NOT_PAIRED, CONNECTION_SUCCESS, CONNECTION_FAIL, DISCONNECT, PAIRING_BUTTON_PRESSED};

  class CBlocks
  {
  private:
    static unsigned int objectID;
    static unsigned int instanceID;
    static Network* network;
    static PowerManager* powerManager;
    static UpdateTimer* batteryStatusUpdateTimer;
    static Pairing* pairing;
    static StatusLED* statusLED;
    // State state;

    static State* statePaired;
    static State* statePairing;
    static State* stateConnected;
    static State* stateNotConnected;
    static Fsm* fsm;

    static void initStateMachine();
    static void publishBatteryStatus();
    static String getOutputTopicFor(unsigned int resourceID);
    static String getInputTopicFor(unsigned int resourceID);

    static void onStatePairedEnter();
    static void onStatePairedUpdate();
    static void onStatePairingEnter();
    static void onStatePairingUpdate();
    static void onStateConnectedEnter();
    static void onStateConnectedUpdate();
    static void onStateNotConnectedEnter();
    static void onStateNotConnectedUpdate();
  public:
    CBlocks(unsigned int objectID, unsigned int instanceID, Network* network, PowerManager* powerManager, Pairing* pairing, StatusLED* statusLED);

    static void begin();
    static void heartBeat();
    static void updateResource(unsigned int resourceID, String value);
    static void updateResource(unsigned int resourceID, unsigned int value);
    static void updateResource(unsigned int resourceID, float value);
    static void updateResource(unsigned int resourceID, bool value);
    static void updateResource(unsigned int resourceID, JsonObject& json);
    static void registerCommand(unsigned int resourceID, commandCallback cb);
  };
}

#endif
