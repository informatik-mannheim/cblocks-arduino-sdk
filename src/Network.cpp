#include "Network.h"
#include "Command.h"
#include "Link.h"
#include "Util.h"

namespace CBlocks{
  Link* Network::link = NULL;
  String Network::clientID = String("");
  Will Network::firstWill = Will();
  Will Network::lastWill = Will();
  MQTT Network::mqtt = MQTT();
  DynamicJsonBuffer* Network::jsonBuffer = new DynamicJsonBuffer();
  JsonObject* Network::commandJson = &(jsonBuffer->createObject());
  String Network::commandTopic = String("");
  String Network::commandClientID = String("");
  CommandResponse Network::commandResponse = CommandResponse();
  SimpleList<Subscription*> Network::subscriptions = SimpleList<Subscription*>();

  Network::Network(Link* link, String clientID, MQTT mqtt, Will firstWill, Will lastWill){
    this->link = link;
    this->clientID = clientID;
    this->mqtt = mqtt;
    this->firstWill = firstWill;
    this->lastWill = lastWill;
  }

  void Network::begin(){
    initMQTTClient();
  }

  void Network::initMQTTClient(){
    mqtt.client->setServer(mqtt.host, mqtt.port);
    mqtt.client->setCallback(Network::subscriptionCallback);
  }

  void Network::subscriptionCallback(char *topic, byte *payload, unsigned int length){
    parseCommand(topic, payload, length);

    if(commandSuccessfullyParsed()){
      getCommandResponse();
      respondToCommandIfRequestIDPresent();
    }
  }

  void Network::parseCommand(char *topic, byte *payload, unsigned int length){
    commandTopic = Util::removeClientIDFromCommandTopic(topic);
    commandJson = &Util::getJSONForPayload(payload, length, *jsonBuffer);
    commandClientID = Util::getClientIDFromCommandTopic(String(topic));
  }

  bool Network::commandSuccessfullyParsed(){
    return commandJson->success();
  }

  void Network::getCommandResponse(){
    if(commandHasValidCommandData()){
      getResponseFromCommandCallback();
    }else{
      getValidationErrorResponse();
    }
  }

  bool Network::commandHasValidCommandData(){
    return (Util::validateCommandData(*commandJson).length() == 0);
  }

  void Network::getResponseFromCommandCallback(){
    for(SimpleList<Subscription*>::iterator itr = subscriptions.begin(); itr != subscriptions.end();){
      if((*itr)->topic.equals(commandTopic)){
        Serial.println("Calling cb for " + commandTopic);
        commandResponse = (*itr)->cb(*commandJson);
        return;
      }

      ++itr;
    }
  }

  void Network::getValidationErrorResponse(){
    commandResponse.success = false;
    commandResponse.requestID = commandJson->get<long>("requestID");
    commandResponse.message = Util::validateCommandData(*commandJson);
  }

  void Network::respondToCommandIfRequestIDPresent(){
    if(commandHasValidRequestID()){
      publish(Util::getResponseTopic(commandClientID), commandResponse.toJSON(*jsonBuffer));
    }
  }

  bool Network::commandHasValidRequestID(){
    return (Util::validateCommandRequestID(*commandJson).length() == 0);
  }

  bool Network::ensureConnected(){
    if(!link->isConnected() && !link->connect()){
      return false;
    }

    if(!mqtt.client->connected()) {
      Serial.print("Attempting MQTT connection to ");
      Serial.println(mqtt.host);

      if (connectIsSuccessfull()) {
        Serial.println("connected");

        subsribeToCommandTopics();
      } else {
        Serial.print("failed, rc=");
        Serial.print(mqtt.client->state());

        return false;
      }
    }

    mqtt.client->loop();

    return true;
  }

  bool Network::connectIsSuccessfull(){
    return mqtt.client->connect(clientID.c_str(), mqtt.username, mqtt.password, lastWill.topic.c_str(), lastWill.qos, lastWill.retain, lastWill.message.c_str());
  }

  void Network::subsribeToCommandTopics(){
    for(SimpleList<Subscription*>::iterator itr = subscriptions.begin(); itr != subscriptions.end();){
      subscribe((*itr)->topic);
      ++itr;
    }
  }

  void Network::publishFirstWill(){
    ensureConnected();
    mqtt.client->publish(firstWill.topic.c_str(), firstWill.message.c_str(), true);
  }

  void Network::publishLastWill(){
    ensureConnected();
    mqtt.client->publish(lastWill.topic.c_str(), lastWill.message.c_str(), true);
  }

  void Network::publish(String topic, String payload){
    ensureConnected();
    mqtt.client->publish(topic.c_str(), payload.c_str());
  }

  void Network::subscribe(String topic, commandCallback cb){
    addSubscription(topic, cb);

    if(isConnected()){
      subscribe(topic);
    }
  }

  void Network::addSubscription(String topic, commandCallback cb){
    Subscription* s = new Subscription();
    s->topic = topic;
    s->cb = cb;

    subscriptions.push_back(s);
  }

  void Network::subscribe(String topic){
    Serial.println("Subscribed to " + topic);
    mqtt.client->subscribe(topic.c_str());
  }

  void Network::disconnect(){
    if(!isConnected()){
      return;
    }

    publishLastWill();
    mqtt.client->disconnect();
    link->disconnect();
    Serial.println("Disconnected from Network");
  }

  bool Network::isConnected(){
    return (link->isConnected() && mqtt.client->connected());
  }
}
