#include "Network.h"

Network::Network(String clientID, MQTT mqtt, Will firstWill, Will lastWill){
  this->clientID = clientID;
  this->mqtt = mqtt;
  this->firstWill = firstWill;
  this->lastWill = lastWill;
}

void Network::init(){
  initMQTTClient();
  publishFirstWill();
}

void Network::initMQTTClient(){
  mqtt.client->setServer(mqtt.host, mqtt.port);
  ensureConnected();
}

void Network::ensureConnected(){
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

bool Network::connectIsSuccessfull(){
  return mqtt.client->connect(clientID.c_str(), mqtt.username, mqtt.password, lastWill.topic.c_str(), lastWill.qos, lastWill.retain, lastWill.message.c_str());
}

void Network::publishFirstWill(){
  ensureConnected();
  mqtt.client->publish(firstWill.topic.c_str(), firstWill.message.c_str(), true);
}

void Network::publish(String topic, String payload){
  ensureConnected();
  mqtt.client->publish(topic.c_str(), payload.c_str());
}
