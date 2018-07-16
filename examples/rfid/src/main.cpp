#include "Arduino.h"
#include "MQTTConf.h"
#include "CBlocks.h"
#include "CBlocksMaker.h"
#include "RFID.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "StatusLED.h"
#include "Link.h"
#include "WiFiLink.h"

#define BAUD_RATE 115200
#define OBJECT_ID 3305
#define INSTANCE_ID 0
#define STATUS_RED_PIN 0
#define STATUS_GREEN_PIN 15
#define SSID "cblocks-gateway"
#define PASSWORD "naeheaufdistanz"
#define RST_PIN 4
#define SS_PIN 5
#define BUZZER_PIN 2

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks::CBlocks* cblocks;
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(STATUS_RED_PIN, STATUS_GREEN_PIN);
CBlocks::Link* link = new CBlocks::WiFiLink(SSID, PASSWORD);
CBlocks::CardReader* cardReader;
MFRC522 mfrc522(SS_PIN, RST_PIN);

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void init_cblocks(){
  cblocks = CBlocks::makeMQTT(OBJECT_ID, INSTANCE_ID, link, mqtt, statusLED);
  cblocks->begin();
}

void init_sensor(){
  cardReader = new CBlocks::CardReader(&mfrc522, cblocks, BUZZER_PIN);
  cardReader->begin();
}

void setup(){
  initAndWaitForSerial();
  init_cblocks();
  init_sensor();
}

void loop(){
  cardReader->publishStatus();
}
