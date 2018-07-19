#include "CBlocks.h"
#include "Util.h"
#include "UpdateTimer.h"
#include "Pairing.h"
#include "StatusLED.h"
#include "Fsm.h"

namespace CBlocks{
  State* CBlocks::statePaired = NULL;
  State* CBlocks::statePairing = NULL;
  State* CBlocks::stateConnected = NULL;
  State* CBlocks::stateNotConnected = NULL;
  Fsm* CBlocks::fsm = NULL;
  unsigned int CBlocks::objectID;
  unsigned int CBlocks::instanceID ;
  Network* CBlocks::network = NULL;
  PowerManager* CBlocks::powerManager = NULL;
  UpdateTimer* CBlocks::batteryStatusUpdateTimer = NULL;
  Pairing* CBlocks::pairing = NULL;
  StatusLED* CBlocks::statusLED = NULL;


  CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, Network* network, PowerManager* powerManager, Pairing* pairing, StatusLED* statusLED){
    this->objectID = objectID;
    this->instanceID = instanceID;
    this->network = network;
    this->powerManager = powerManager;
    this->batteryStatusUpdateTimer = new UpdateTimer(BATTERY_STATUS_UPDATE_INTERVAL_MS);
    this->pairing = pairing;
    this->statusLED = statusLED;

    statePaired = new State(onStatePairedEnter, onStatePairedUpdate, NULL);
    statePairing = new State(onStatePairingEnter, onStatePairingUpdate, NULL);
    stateConnected = new State(onStateConnectedEnter, onStateConnectedUpdate, NULL);
    stateNotConnected = new State(onStateNotConnectedEnter, onStateNotConnectedUpdate, NULL);
  }

  void CBlocks::begin(){
    powerManager->begin();
    pairing->begin();
    network->begin();

    initStateMachine();
  }

  void CBlocks::initStateMachine(){
    if(pairing->isPaired()){
      fsm = new Fsm(statePaired);
    }else{
      fsm = new Fsm(stateNotConnected);
    }

    fsm->add_transition(statePaired, stateConnected, StateTransition::CONNECTION_SUCCESS, NULL);
    fsm->add_transition(statePaired, stateNotConnected, StateTransition::CONNECTION_FAIL, NULL);
    fsm->add_transition(stateConnected, statePairing, StateTransition::PAIRING_BUTTON_PRESSED, NULL);
    fsm->add_transition(stateNotConnected, statePairing, StateTransition::PAIRING_BUTTON_PRESSED, NULL);
    fsm->add_transition(statePairing, statePaired, StateTransition::IS_PAIRED, NULL);
    fsm->add_transition(statePairing, stateNotConnected, StateTransition::PAIRING_BUTTON_PRESSED, NULL);
  }

  void CBlocks::onStatePairedEnter(){
    Serial.println("State paired");
    network->disconnect();
    statusLED->connecting();

    network->ensureConnected();
  }

  void CBlocks::onStatePairedUpdate(){
    if(network->isConnected()){
      fsm->trigger(StateTransition::CONNECTION_SUCCESS);
    }else{
      fsm->trigger(StateTransition::CONNECTION_FAIL);
    }
  }

  void CBlocks::onStatePairingEnter(){
    Serial.println("State pairing");
    statusLED->pairing();
    pairing->reset();
  }

  void CBlocks::onStatePairingUpdate(){
    if(!pairing->isPairingButtonOn()){
      pairing->pair();

      if(pairing->isPaired()){
        fsm->trigger(StateTransition::IS_PAIRED);
      }
    }else{
      fsm->trigger(StateTransition::PAIRING_BUTTON_PRESSED);
    }
  }

  void CBlocks::onStateConnectedEnter(){
    Serial.println("State connected");
    statusLED->running();
  }

  void CBlocks::onStateConnectedUpdate(){
    publishBatteryStatus();

    if(pairing->isPairingButtonOn()){
      fsm->trigger(StateTransition::PAIRING_BUTTON_PRESSED);
    }
  }

  void CBlocks::onStateNotConnectedEnter(){
    Serial.println("State Not connected");
    statusLED->error();
  }

  void CBlocks::onStateNotConnectedUpdate(){
    if(pairing->isPairingButtonOn()){
      fsm->trigger(StateTransition::PAIRING_BUTTON_PRESSED);
    }
  }

  void CBlocks::heartBeat(){
    if(shouldTurnOff()){
      network->disconnect();
      powerManager->turnOff();
    }

    fsm->run_machine();
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
    if(!network->isConnected()) return;

    network->publish(getOutputTopicFor(resourceID), value);
  }

  void CBlocks::updateResource(unsigned int resourceID, unsigned int value){
    if(!network->isConnected()) return;

    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  String CBlocks::getOutputTopicFor(unsigned int resourceID){
    return Util::getOutputTopic(objectID, instanceID, resourceID);
  }

  void CBlocks::updateResource(unsigned int resourceID, float value){
    if(!network->isConnected()) return;

    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::updateResource(unsigned int resourceID, bool value){
    if(!network->isConnected()) return;

    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::updateResource(unsigned int resourceID, JsonObject& value){
    if(!network->isConnected()) return;

    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::registerCommand(unsigned int resourceID, commandCallback cb){
    network->subscribe(getInputTopicFor(resourceID), cb);
  }

  String CBlocks::getInputTopicFor(unsigned int resourceID){
    return Util::getInputTopic(objectID, instanceID, resourceID);
  }
}
