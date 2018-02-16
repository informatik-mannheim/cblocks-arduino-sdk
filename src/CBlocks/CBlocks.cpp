#include "CBlocks.h"
#include "Util.h"

CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, MQTT mqtt){
  this->objectID = objectID;
  this->instanceID = instanceID;
  this->clientID = Util::getClientID(objectID, instanceID);
  this->mqtt = mqtt;
}

void CBlocks::begin(){
  initMQTTClient();
  publishFirstWill();
}

void CBlocks::initMQTTClient(){
  mqtt.client->setServer(mqtt.host, mqtt.port);
  ensureConnected();
}

void CBlocks::ensureConnected(){
  while (!mqtt.client->connected()) {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(String(mqtt.host) + String(" "));

    if (connectIsSuccessfull()) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt.client->state());
      Serial.println(" trying again ...");
      delay(RECONNECT_TIME_IN_MS);
    }
  }
  mqtt.client->loop();
}

bool CBlocks::connectIsSuccessfull(){
  Will lastWill = Util::getLastWillFor(objectID, instanceID);

  return mqtt.client->connect(clientID.c_str(), mqtt.username, mqtt.password, lastWill.topic.c_str(), lastWill.qos, lastWill.retain, lastWill.message.c_str());
}

void CBlocks::publishFirstWill(){
  ensureConnected();
  Will firstWill = Util::getFirstWillFor(objectID, instanceID);
  mqtt.client->publish(firstWill.topic.c_str(), firstWill.message.c_str(), true);
}

String CBlocks::getNamedTopicFor(String resourceName){
  return Util::getNamedTopic(objectID, instanceID, resourceName);
}

void CBlocks::updateResource(unsigned int resourceID, unsigned int value){
  ensureConnected();
  mqtt.client->publish(getOutputTopicFor(resourceID).c_str(), Util::getPayloadFor(value).c_str());
}

String CBlocks::getOutputTopicFor(unsigned int resourceID){
  return Util::getOutputTopic(objectID, instanceID, resourceID);
}

void CBlocks::updateResource(unsigned int resourceID, float value){
  ensureConnected();
  mqtt.client->publish(getOutputTopicFor(resourceID).c_str(), Util::getPayloadFor(value).c_str());
}
