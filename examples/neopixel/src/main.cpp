#include "Arduino.h"
#include "MQTTConf.h"
#include "CBlocks.h"
#include "Network.h"
#include "CBlocksMaker.h"
#include "Neopixel.h"
#include "Adafruit_NeoPixel.h"
#include "StatusLED.h"
#include "Link.h"
#include "WiFiLink.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BAUD_RATE 115200
#define OBJECT_ID 3304
#define INSTANCE_ID 0
#define NUMBER_OF_PIXELS 4
#define PIXEL_PIN 2
#define STATUS_PIXEL 0
#define NEOPIXEL_OFFSET 1
#define SSID "cblocks-gateway"
#define PASSWORD "naeheaufdistanz"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks::CBlocks* cblocks;
CBlocks::Neopixel* neopixel;
Adafruit_NeoPixel* strip = new Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(strip, STATUS_PIXEL);
CBlocks::Link* link = new CBlocks::WiFiLink(SSID, PASSWORD);

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
}

void init_cblocks(){
  cblocks = CBlocks::makeMQTT(OBJECT_ID, INSTANCE_ID, link, mqtt, statusLED);
  cblocks->begin();
}

void init_sensor(){
  neopixel = new CBlocks::Neopixel(strip, cblocks, NEOPIXEL_OFFSET);
  neopixel->begin();
}

void setup(){
  strip->begin();
  initAndWaitForSerial();
  init_cblocks();
  init_sensor();
}

void loop(){
  neopixel->publishStatus();
}
