#ifndef NETWORK_H
#define NETWORK_H

#include "Arduino.h"
#include "PubSubClient.h"
#include "ArduinoJson.h"
#include "Will.h"

#define RECONNECT_TIME_IN_MS 5000

struct MQTT {
  PubSubClient* client;
  const char* host;
  unsigned int port;
  const char* username;
  const char* password;
};

class Network{
private:
  String clientID;
  Will firstWill;
  Will lastWill;
  MQTT mqtt;
  DynamicJsonBuffer jsonBuffer;

  void initMQTTClient();
  void ensureConnected();
  bool connectIsSuccessfull();
  void publishFirstWill();
public:
  Network(String clientID, MQTT mqtt, Will firstWill, Will lastWill);
  void init();
  void publish(String topic, String payload);
};

#endif
