#ifndef NETWORK_H
#define NETWORK_H

#include "Arduino.h"
#include "PubSubClient.h"
#include "ArduinoJson.h"
#include "Will.h"
#include "Command.h"
#include "SimpleList.h"
#include "Link.h"

#define RECONNECT_TIME_IN_MS 5000

namespace CBlocks{
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
    static Link* link;
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

    void setupLink();
    void initMQTTClient();
    static bool connectIsSuccessfull();
    void publishLastWill();
    void addSubscription(String topic, commandCallback cb);

    static void subscriptionCallback(char* topic, byte* payload, unsigned int length);
    static void parseCommand(char *topic, byte *payload, unsigned int length);
    static bool commandSuccessfullyParsed();
    static void getCommandResponse();
    static bool commandHasValidCommandData();
    static void getValidationErrorResponse();
    static void getResponseFromCommandCallback();
    static void respondToCommandIfRequestIDPresent();
    static bool commandHasValidRequestID();
    static void subscribe(String topic);
    static void subsribeToCommandTopics();
  public:
    Network(Link* link, String clientID, MQTT mqtt, Will firstWill, Will lastWill);
    void begin();
    bool isConnected();
    static bool ensureConnected();
    static void publish(String topic, String payload);
    void subscribe(String topic, commandCallback cb);
    void disconnect();
    void publishFirstWill();
  };
}

#endif
