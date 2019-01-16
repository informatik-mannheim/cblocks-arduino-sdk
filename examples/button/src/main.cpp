#include "MQTTConf.h"
#include "CBlocks.h"
#include "Network.h"
#include "CBlocksMaker.h"
#include "Adafruit_NeoPixel.h"
#include "StatusLED.h"
#include "Link.h"
#include "WiFiLink.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "PowerManager.h"
#include "ESP32PowerManager.h"
#include "HX711.h"
#include "Pairing.h"
#include "AudioPairing.h"
#include "AstroMac.h"
#include "EEPROM.h"
#include "Adafruit_MCP3008.h"

#define BAUD_RATE 115200
#define OBJECT_ID 3302
#define INSTANCE_ID 0
#define PIXEL_PIN 14
#define STATUS_PIXEL 0
#define NUMBER_OF_PIXELS 5
#define PAIRING_MODE_PIN 27
#define SS 15
#define BATTERY_STATUS_PIN A9
#define MIC_PIN A0
#define ENABLE_PIN 12
#define SHUT_DOWN_PIN 13

Adafruit_MCP3008 adc;
int analogReadFP(uint8_t pin){
  return adc.readADC(pin);
}

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks::CBlocks* cblocks;
Adafruit_NeoPixel* strip = new Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIXEL_PIN, NEO_RGB + NEO_KHZ800);
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(strip, STATUS_PIXEL);
CBlocks::WiFiLink* wifiLink = new CBlocks::WiFiLink();
AstroMac::AstroMac* astroMac = new AstroMac::AstroMac(analogReadFP, MIC_PIN);
CBlocks::Pairing* pairing = new CBlocks::AudioPairing(PAIRING_MODE_PIN, wifiLink, astroMac);
CBlocks::PowerManager* powerManager = new CBlocks::ESP32PowerManager(ENABLE_PIN, SHUT_DOWN_PIN, BATTERY_STATUS_PIN);

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  adc.begin(SS);
  delay(1000);
}

void init_cblocks(){
  cblocks = CBlocks::makeMQTT(OBJECT_ID, INSTANCE_ID, (CBlocks::Link*)wifiLink, mqtt, statusLED, powerManager, pairing);
  cblocks->begin();
}

void init_sensor(){
  //TODO: button lib
}

void setup(){
  initAndWaitForSerial();
  init_cblocks();
  init_sensor();
}

void loop(){
}
