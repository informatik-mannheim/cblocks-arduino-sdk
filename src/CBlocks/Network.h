#ifndef NETWORK_H
#define NETWORK_H

#include "Arduino.h"
#include "PubSubClient.h"
#include "ArduinoJson.h"
#include "Will.h"
#include "Command.h"
#include "SimpleList.h"

#define RECONNECT_TIME_IN_MS 5000

struct MQTT {
  PubSubClient* client;
  const char* host;
  unsigned int port;
  const char* username;
  const char* password;
};

struct Subscription{
  String topic;
  commandCallback cb;
};

class Network{
private:
  static String clientID;
  static Will firstWill;
  static Will lastWill;
  static MQTT mqtt;
  static DynamicJsonBuffer* jsonBuffer;
  static JsonObject* commandJson;
  static String commandTopic;
  static String commandClientID;
  static CommandResponse commandResponse;
  static SimpleList<Subscription*> subscriptions;

  void initMQTTClient();
  static void ensureConnected();
  static bool connectIsSuccessfull();
  void publishFirstWill();
  void addSubscription(String topic, commandCallback cb);
  void subscribe(String topic);
  static void subscriptionCallback(char* topic, byte* payload, unsigned int length);
  static void parseCommand(char *topic, byte *payload, unsigned int length);
  static bool commandSuccessfullyParsed();
  static void getCommandResponse();
  static bool commandHasValidCommandData();
  static void getValidationErrorResponse();
  static void getResponseFromCommandCallback();
  static void respondToCommandIfRequestIDPresent();
  static bool commandHasValidRequestID();
public:
  Network(String clientID, MQTT mqtt, Will firstWill, Will lastWill);
  void init();
  static void publish(String topic, String payload);
  void subscribe(String topic, commandCallback cb);
};

#endif
