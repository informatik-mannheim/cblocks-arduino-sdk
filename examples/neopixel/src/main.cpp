#include "Arduino.h"
#include "MQTTConf.h"
#include "CBlocks.h"
#include "Network.h"
#include "CBlocksMaker.h"
#include "Neopixel.h"
#include "Adafruit_NeoPixel.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BAUD_RATE 115200
#define OBJECT_ID 3304
#define INSTANCE_ID 0
#define NUMBER_OF_PIXELS 4
#define PIXEL_PIN 2

const char* ssid = "cblocks-gateway";
const char* password = "naeheaufdistanz";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks* cblocks;
Network* network;
Neopixel::Neopixel* neopixel;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIXEL_PIN);

const unsigned int UPDATE_INTERVAL_IN_MS = 500;

void initAndWaitForSerial(){
  Serial.begin(BAUD_RATE);
  delay(2000);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void init_cblocks(){
  cblocks = makeMQTT(OBJECT_ID, INSTANCE_ID, mqtt);
  cblocks->begin();
}

void init_sensor(){
  neopixel = new Neopixel::Neopixel(&strip, cblocks);
  neopixel->begin();
}

void setup(){
  initAndWaitForSerial();
  setup_wifi();
  init_cblocks();
  init_sensor();
}

void loop(){
  delay(UPDATE_INTERVAL_IN_MS);
  neopixel->publishStatus();
}
