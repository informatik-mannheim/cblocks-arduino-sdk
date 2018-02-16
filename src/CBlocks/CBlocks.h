#ifndef CBLOCKS_H
#define CBLOCKS_H

#include "Arduino.h"
#include <PubSubClient.h>

#define RECONNECT_TIME_IN_MS 5000

struct MQTT {
  PubSubClient* client;
  const char* host;
  unsigned int port;
  const char* username;
  const char* password;
};

class CBlocks
{
private:
  unsigned int objectID;
  unsigned int instanceID;
  String clientID;
  MQTT mqtt;

  String getNamedTopicFor(String resourceName);
  String getOutputTopicFor(unsigned int resourceID);
  void initMQTTClient();
  void ensureConnected();
  bool connectIsSuccessfull();
  void publishFirstWill();

public:
  CBlocks(unsigned int objectID, unsigned int instanceID, MQTT mqtt);

  void begin();
  void updateResource(unsigned int resourceID, unsigned int value);
};

#endif
