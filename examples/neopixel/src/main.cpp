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
#define STATUS_RED_PIN 15
#define STATUS_GREEN_PIN 13

const char* ssid = "cblocks-gateway";
const char* password = "naeheaufdistanz";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks::CBlocks* cblocks;
CBlocks::Neopixel* neopixel;
Adafruit_NeoPixel* strip = new Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIXEL_PIN);
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(STATUS_RED_PIN, STATUS_GREEN_PIN);
CBlocks::Link* link = new CBlocks::WiFiLink(ssid, password);

const unsigned int UPDATE_INTERVAL_IN_MS = 500;

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void init_cblocks(){
  cblocks = CBlocks::makeMQTT(OBJECT_ID, INSTANCE_ID, link, mqtt, statusLED);
  cblocks->begin();
}

void init_sensor(){
  neopixel = new CBlocks::Neopixel(strip, cblocks);
  neopixel->begin();
}

void setup(){
  initAndWaitForSerial();
  init_cblocks();
  init_sensor();
}

void loop(){
  delay(UPDATE_INTERVAL_IN_MS);
  neopixel->publishStatus();
}
