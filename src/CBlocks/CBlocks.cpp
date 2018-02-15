#include "CBlocks.h"
#include "Util.h"

CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, MQTT mqtt){
  this->objectID = objectID;
  this->instanceID = instanceID;
  this->clientID = Util::getClientID(objectID, instanceID).c_str();
  this->mqtt = mqtt;
}

void CBlocks::begin(){
  initMQTTClient();
}

void CBlocks::initMQTTClient(){
  mqtt.client->setServer(mqtt.host, mqtt.port);
  ensureConnected();
}

void CBlocks::updateResource(unsigned int resourceID, unsigned int value){
  ensureConnected();
  mqtt.client->publish(getOutputTopicFor(resourceID).c_str(), Util::getPayloadFor(value).c_str());
}

void CBlocks::ensureConnected(){
  while (!mqtt.client->connected()) {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(String(mqtt.host) + String(" "));

    if (mqtt.client->connect(clientID, mqtt.username, mqtt.password)) {
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

String CBlocks::getOutputTopicFor(unsigned int resourceID){
  return Util::getOutputTopic(objectID, instanceID, resourceID);
}
