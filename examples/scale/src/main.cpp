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
#include "UsbPowerManager.h"
#include "Pairing.h"
#include "HardcodedPairing.h"
#include "HX711.h"
#include "Scale.h"

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

HX711* hx711 = new HX711(HX711_DOUT_PIN, HX711_CLK_PIN);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks::CBlocks* cblocks;
Adafruit_NeoPixel* strip = new Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(strip, STATUS_PIXEL);
CBlocks::WiFiLink* wifiLink = new CBlocks::WiFiLink();
CBlocks::Pairing* pairing = new CBlocks::HardcodedPairing("cblocks-gateway", "naeheaufdistanz", wifiLink);
CBlocks::PowerManager* powerManager = new CBlocks::UsbPowerManager();
CBlocks::Scale* scale;

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
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
  strip->begin();
  initAndWaitForSerial();
  init_cblocks();
  init_sensor();
}

void loop(){
  scale->publishStatus();
}
