#include "Arduino.h"
#include "MQTTConf.h"
#include "CBlocks.h"
#include "Command.h"
#include "Network.h"
#include "CBlocksMaker.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BAUD_RATE 115200
#define OBJECT_ID 3303
#define INSTANCE_ID 0
#define LED_PIN 2

const char* ssid = "cblocks-gateway";
const char* password = "naeheaufdistanz";

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

//TODO connect LED
CommandResponse cb(JsonObject& json){
  CommandResponse response;
  response.requestID = json["requestID"];

  if(json.is<bool>("data")){
    digitalWrite(LED_PIN, json.get<bool>("data"));

    response.success = true;
    response.message = String("LED set");
  }else{
    response.success = false;
    response.message = String("Data must be of type bool in order to set LED.");
  }

  return response;
}

void init_cblocks(){
  cblocks = makeMQTT(OBJECT_ID, INSTANCE_ID, mqtt);
  cblocks->begin();

  cblocks->registerCommand(0, cb);
}

void init_pins(){
  pinMode(LED_PIN, OUTPUT);
}

void setup(){
  initAndWaitForSerial();
  setup_wifi();
  init_cblocks();
  init_pins();
}

void loop(){
  delay(1000);
  cblocks->updateResource(0, (unsigned int)random(0, 50));
}
