#include "Network.h"
#include "Command.h"
#include "Util.h"

String Network::clientID = String("");
Will Network::firstWill = Will();
Will Network::lastWill = Will();
MQTT Network::mqtt = MQTT();
DynamicJsonBuffer* Network::jsonBuffer = new DynamicJsonBuffer();
SimpleList<Subscription*> Network::subscriptions = SimpleList<Subscription*>();

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
  mqtt.client->setCallback(Network::subscriptionCallback);
  ensureConnected();
}

void Network::subscriptionCallback(char *topic, byte *payload, unsigned int length){
  JsonObject& json = Util::getJSONForPayload(payload, length, *jsonBuffer);
  String clientID = Util::getClientIDFromCommandTopic(String(topic));
  String validation = Util::validateCommandRequestID(json);

  // invalid request id
  if(validation.length()){
    return;
  }

  validation = Util::validateCommandData(json);

  CommandResponse response;

  // invalid data
  if(validation.length()){
    response.success = false;
    response.requestID = json["requestID"];
    response.message = validation;
    publish(Util::getResponseTopic(clientID), response.toJSON(*jsonBuffer));
    return;
  }

  response = callCommandCallbackFor(String(topic), json);

  publish(Util::getResponseTopic(clientID), response.toJSON(*jsonBuffer));
}

CommandResponse Network::callCommandCallbackFor(String topic, JsonObject& json){
  topic = Util::removeClientIDFromCommandTopic(topic);
  for(SimpleList<Subscription*>::iterator itr = subscriptions.begin(); itr != subscriptions.end();){
    if((*itr)->topic.equals(topic)){
      return (*itr)->cb(json);
    }

    ++itr;
  }

  return CommandResponse();
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

void Network::subscribe(String topic, commandCallback cb){
  addSubscription(topic, cb);
  ensureConnected();
  subscribe(topic);
}

void Network::addSubscription(String topic, commandCallback cb){
  Subscription* s = new Subscription();
  s->topic = topic;
  s->cb = cb;

  subscriptions.push_back(s);
}

void Network::subscribe(String topic){
  mqtt.client->subscribe(topic.c_str());
}
