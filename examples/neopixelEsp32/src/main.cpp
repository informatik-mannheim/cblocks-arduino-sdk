#include "MQTTConf.h"
#include "CBlocks.h"
#include "Network.h"
#include "CBlocksMaker.h"
#include "Neopixel.h"
#include "Adafruit_NeoPixel.h"
#include "StatusLED.h"
#include "Link.h"
#include "WiFiLink.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "PowerManager.h"
#include "ESP32PowerManager.h"

#define BAUD_RATE 115200
#define OBJECT_ID 3304
#define INSTANCE_ID 1
#define NUMBER_OF_PIXELS 2
#define PIXEL_PIN 14
#define STATUS_PIXEL 1
#define NUMBER_OF_NEOPIXELS 1
#define POWER_PIN 32
#define WAKE_UP_PIN GPIO_NUM_33
#define BATTERY_STATUS_PIN A3

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks::CBlocks* cblocks;
CBlocks::Neopixel* neopixel;
Adafruit_NeoPixel* strip = new Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(strip, STATUS_PIXEL);
CBlocks::Pairing* pairing = new CBlocks::Pairing();
CBlocks::Link* wifiLink = new CBlocks::WiFiLink(pairing); //TODO pairing in cblocks und credentials per methodenaufruf
CBlocks::PowerManager* powerManager = new CBlocks::ESP32PowerManager(POWER_PIN, WAKE_UP_PIN, PIXEL_PIN, BATTERY_STATUS_PIN);

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
}

void init_cblocks(){
  cblocks = CBlocks::makeMQTT(OBJECT_ID, INSTANCE_ID, wifiLink, mqtt, statusLED, powerManager);
  cblocks->begin();
}

void init_sensor(){
  neopixel = new CBlocks::Neopixel(strip, cblocks, NUMBER_OF_NEOPIXELS);
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
  // digitalWrite(14, HIGH);
  // digitalWrite(32, LOW);
}
