#include "CBlocks.h"
#include "Util.h"
#include "UpdateTimer.h"
#include "Pairing.h"
#include "StatusLED.h"

namespace CBlocks{
  CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, Network* network, PowerManager* powerManager, Pairing* pairing, StatusLED* statusLED){
    this->objectID = objectID;
    this->instanceID = instanceID;
    this->network = network;
    this->powerManager = powerManager;
    this->batteryStatusUpdateTimer = new UpdateTimer(BATTERY_STATUS_UPDATE_INTERVAL_MS);
    this->pairing = pairing;
    this->statusLED = statusLED;
  }

  void CBlocks::begin(){
    powerManager->begin();
    pairing->begin();
    network->begin();

    if(pairing->isPaired()){
      state = PAIRED;
    }else{
      state = CONNECTION_FAILED;
    }
  }

  void CBlocks::heartBeat(){
    if(shouldTurnOff()){
      network->disconnect();
      powerManager->turnOff();
    }

    switch (state) {
      case PAIRED: {
        network->disconnect();
        statusLED->connecting();

        if(network->ensureConnected()){
          state = CONNECTED;
        }else{
          state = CONNECTION_FAILED;
        }

        break;
      }
      case PAIRING: {
        statusLED->pairing();

        if(pairing->isInPairingMode()){
          pairing->pair();
        }else{
          if(pairing->isPaired()){
            state = PAIRED;
          }else{
            state = CONNECTION_FAILED;
          }
        }

        break;
      }
      case CONNECTED:{
        statusLED->running();
        publishBatteryStatus();

        if(pairing->isInPairingMode()){
          state = PAIRING;
        }

        break;
      }
      case CONNECTION_FAILED: {
        statusLED->error();

        if(pairing->isInPairingMode()){
          state = PAIRING;
        }

        break;
      }
    }
  }

  bool CBlocks::shouldTurnOff(){
    return (!powerManager->isPowerButtonOn() || powerManager->isBatteryLow());
  }

  void CBlocks::publishBatteryStatus(){
    if(batteryStatusUpdateTimer->updateIntervalExceeded()){
      updateResource(BATTERY_STATUS_RESOURCE_ID, (unsigned int)powerManager->getBatteryStatus());
    }
  }

  void CBlocks::updateResource(unsigned int resourceID, String value){
    if(state != CONNECTED) return;

    network->publish(getOutputTopicFor(resourceID), value);
  }

  void CBlocks::updateResource(unsigned int resourceID, unsigned int value){
    if(state != CONNECTED) return;

    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  String CBlocks::getOutputTopicFor(unsigned int resourceID){
    return Util::getOutputTopic(objectID, instanceID, resourceID);
  }

  void CBlocks::updateResource(unsigned int resourceID, float value){
    if(state != CONNECTED) return;

    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::updateResource(unsigned int resourceID, bool value){
    if(state != CONNECTED) return;

    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::updateResource(unsigned int resourceID, JsonObject& value){
    if(state != CONNECTED) return;

    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::registerCommand(unsigned int resourceID, commandCallback cb){
    network->subscribe(getInputTopicFor(resourceID), cb);
  }

  String CBlocks::getInputTopicFor(unsigned int resourceID){
    return Util::getInputTopic(objectID, instanceID, resourceID);
  }
}
