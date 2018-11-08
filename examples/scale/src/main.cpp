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
#include "Scale.h"
#include "Pairing.h"
#include "AudioPairing.h"
#include "AstroMac.h"
#include "EEPROM.h"
#include "Adafruit_MCP3008.h"

#define BAUD_RATE 115200
#define OBJECT_ID 3306
#define INSTANCE_ID 0
#define PIXEL_PIN 14
#define STATUS_PIXEL 0
#define NUMBER_OF_PIXELS 1
#define HX711_DOUT_PIN 23
#define HX711_CLK_PIN 22
#define HX711_CALIBRATION_FACTOR -206
#define TARE_PIN 4
#define PAIRING_MODE_PIN 27
#define SS 15
#define BATTERY_STATUS_PIN A3

Adafruit_MCP3008 adc;
int analogReadFP(uint8_t pin){
  return adc.readADC(pin);
}

HX711* hx711 = new HX711(HX711_DOUT_PIN, HX711_CLK_PIN);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks::CBlocks* cblocks;
Adafruit_NeoPixel* strip = new Adafruit_NeoPixel(5, PIXEL_PIN, NEO_RGB + NEO_KHZ800);
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(strip, STATUS_PIXEL);
CBlocks::WiFiLink* wifiLink = new CBlocks::WiFiLink();
AstroMac::AstroMac* astroMac = new AstroMac::AstroMac(analogReadFP, A0);
CBlocks::Pairing* pairing = new CBlocks::AudioPairing(PAIRING_MODE_PIN, wifiLink, astroMac);
CBlocks::PowerManager* powerManager = new CBlocks::ESP32PowerManager(BATTERY_STATUS_PIN);
CBlocks::Scale* scale;

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
  scale = new CBlocks::Scale(hx711, (long)HX711_CALIBRATION_FACTOR, cblocks, TARE_PIN);
  scale->begin();
}

void setup(){
  initAndWaitForSerial();
  init_cblocks();
  init_sensor();
}

void loop(){
  scale->publishStatus();
}
