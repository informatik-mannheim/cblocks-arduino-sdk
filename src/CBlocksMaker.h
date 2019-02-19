#ifndef CBLOCKS_MAKER_H
#define CBLOCKS_MAKER_H

#include "CBlocks.h"
#include "Link.h"
#include "WiFiLink.h"
#include "StatusLED.h"
#include "Network.h"
#include "Util.h"
#include "PowerManager.h"
#include "Pairing.h"
#include "Adafruit_NeoPixel.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "ESP32PowerManager.h"
#include "AudioPairing.h"
#include "AstroMech.h"
#include "EEPROM.h"
#include "Adafruit_MCP3008.h"

#define PIXEL_PIN 14
#define STATUS_PIXEL 0
#define NUMBER_OF_PIXELS 5
#define PAIRING_MODE_PIN 27
#define SS 15
#define BATTERY_STATUS_PIN A9
#define MIC_PIN 0
#define ENABLE_PIN 12
#define SHUT_DOWN_PIN 13

#define WIFI_SSID "cblocks-gateway"
#define WIFI_PASSWORD "123456789"

#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_HOST "172.16.1.1"
#define MQTT_PORT 1883
#define MQTT_KEEPALIVE 5
#define MQTT_SOCKET_TIMEOUT 5

namespace CBlocks{
  class CBlocksMaker{
  private:
    static WiFiClient* wifiClient;
    static PubSubClient* mqttClient;
    static MQTT* mqtt;
    static WiFiLink* wifiLink;
    static Network* network;
    static Pairing* pairing;

    static Adafruit_NeoPixel* strip;
    static StatusLED* statusLED;

    static PowerManager* powerManager;
  public:
    static CBlocks* make(unsigned int objectID, unsigned int instanceID);
    static CBlocks* makeNoPairing(unsigned int objectID, unsigned int instanceID, String ssid, String password);

    static void setUpNetwork(unsigned int objectID, unsigned int instanceID);
    static void setUpAudioPairing();
    static void setUpHardcodedPairing(String ssid, String password);
  };
}

#endif
