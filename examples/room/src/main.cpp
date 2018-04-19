#include "Arduino.h"
#include "MQTTConf.h"
#include "CBlocks.h"
#include "Network.h"
#include "CBlocksMaker.h"
#include "DHT_U.h"
#include "Room.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "StatusLED.h"
#include "Link.h"
#include "WiFiLink.h"

#define BAUD_RATE 115200
#define OBJECT_ID 3303
#define INSTANCE_ID 0
#define DHTPIN 12
#define DHTTYPE 22
#define STATUS_RED_PIN 13
#define STATUS_GREEN_PIN 15
#define SSID "cblocks-gateway"
#define PASSWORD "naeheaufdistanz"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks::CBlocks* cblocks;
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(STATUS_RED_PIN, STATUS_GREEN_PIN);
CBlocks::Link* link = new CBlocks::WiFiLink(SSID, PASSWORD);
DHT_Unified dht(DHTPIN, DHTTYPE);
CBlocks::Room* roomSensor;

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
}

void init_cblocks(){
  cblocks = CBlocks::makeMQTT(OBJECT_ID, INSTANCE_ID, link, mqtt, statusLED);
  cblocks->begin();
}

void init_sensor(){
  roomSensor = new CBlocks::Room(&dht, cblocks);
  roomSensor->begin();
}

void setup(){
  initAndWaitForSerial();
  init_cblocks();
  init_sensor();
}

void loop(){
  roomSensor->publishStatus();
}
