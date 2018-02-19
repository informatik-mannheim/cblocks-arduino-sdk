#include "Arduino.h"
#include "MQTTConf.h"
#include "CBlocks.h"
#include "Network.h"
#include "Util.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BAUD_RATE 115200
#define OBJECT_ID 3303
#define INSTANCE_ID 0

const char* ssid = "cblocks-gateway";
const char* password = "";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks* cblocks;
Network* network;

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
  network = new Network(Util::getClientID(OBJECT_ID, INSTANCE_ID), mqtt, Util::getFirstWillFor(OBJECT_ID, INSTANCE_ID), Util::getLastWillFor(OBJECT_ID, INSTANCE_ID));

  cblocks = new CBlocks(OBJECT_ID, INSTANCE_ID, network);
  cblocks->begin();
}

void setup(){
  initAndWaitForSerial();
  setup_wifi();
  init_cblocks();
}

void loop(){
  delay(1000);
  cblocks->updateResource(0, (unsigned int)random(0, 50));
}
