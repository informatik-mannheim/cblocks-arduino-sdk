#include "Arduino.h"
#include "MQTTConf.h"
#include "CBlocks.h"
#include "Network.h"
#include "CBlocksMaker.h"
#include "StatusLED.h"
#include "Adafruit_NeoPixel.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BAUD_RATE 115200
#define OBJECT_ID 3303
#define INSTANCE_ID 0
#define NUMBER_OF_PIXELS 1
#define STATUS_RED_PIN 15
#define STATUS_GREEN_PIN 13

const char* ssid = "cblocks-gateway";
const char* password = "naeheaufdistanz";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
CBlocks::CBlocks* cblocks;
CBlocks::Network* network;
CBlocks::StatusLED* statusLED = new CBlocks::StatusLED(STATUS_RED_PIN, STATUS_GREEN_PIN);

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void setup(){
  initAndWaitForSerial();
}

void loop(){
  statusLED->connecting();
  delay(500);
  statusLED->running();
  delay(500);
  statusLED->error();
  delay(500);
}
