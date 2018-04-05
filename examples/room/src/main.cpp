#include "Arduino.h"
#include "MQTTConf.h"
#include "CBlocks.h"
#include "Network.h"
#include "CBlocksMaker.h"
#include "DHT_U.h"
#include "Room.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"

#define BAUD_RATE 115200
#define OBJECT_ID 3303
#define INSTANCE_ID 0
#define DHTPIN 2
#define DHTTYPE 22

const char* ssid = "cblocks-gateway";
const char* password = "naeheaufdistanz";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
MQTT mqtt { &mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };
CBlocks* cblocks;
Network* network;
DHT_Unified dht(DHTPIN, DHTTYPE);
Room::Room* roomSensor;

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
  roomSensor = new Room::Room(&dht, cblocks);
  roomSensor->begin();
}

void setup(){
  initAndWaitForSerial();
  setup_wifi();
  init_cblocks();
  init_sensor();
}

void loop(){
  roomSensor->publishStatus();
}
