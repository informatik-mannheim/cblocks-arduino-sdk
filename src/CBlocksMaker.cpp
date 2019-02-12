#include "CBlocksMaker.h"
#include "CBlocks.h"
#include "Link.h"
#include "WiFiLink.h"
#include "StatusLED.h"
#include "Network.h"
#include "Util.h"
#include "PowerManager.h"
#include "Pairing.h"
#include "Adafruit_NeoPixel.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "ESP32PowerManager.h"
#include "AudioPairing.h"
#include "HardcodedPairing.h"
#include "AstroMech.h"
#include "EEPROM.h"
#include "Adafruit_MCP3008.h"

namespace CBlocks{
  Adafruit_MCP3008* adc = new Adafruit_MCP3008();
  int analogReadFP(uint8_t pin){
    adc->readADC(pin);
  }

  WiFiClient* CBlocksMaker::wifiClient = new WiFiClient();
  PubSubClient* CBlocksMaker::mqttClient = new PubSubClient(*wifiClient);
  MQTT* CBlocksMaker::mqtt = new MQTT;
  WiFiLink* CBlocksMaker::wifiLink = new WiFiLink();
  Pairing* CBlocksMaker::pairing = NULL;
  Network* CBlocksMaker::network = NULL;

  Adafruit_NeoPixel* CBlocksMaker::strip = new Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
  StatusLED* CBlocksMaker::statusLED = new StatusLED(strip, STATUS_PIXEL);

  PowerManager* CBlocksMaker::powerManager = new ESP32PowerManager(ENABLE_PIN, SHUT_DOWN_PIN, BATTERY_STATUS_PIN);

  CBlocks* CBlocksMaker::make(unsigned int objectID, unsigned int instanceID){
    setUpNetwork(objectID, instanceID);
    setUpAudioPairing();

    return new CBlocks(objectID, instanceID, network, powerManager, pairing, statusLED);
  }

  void CBlocksMaker::setUpNetwork(unsigned int objectID, unsigned int instanceID){
    *mqtt = { mqttClient, MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD };

    String clientID = Util::getClientID(objectID, instanceID);
    Will firstWill = Util::getFirstWillFor(objectID, instanceID);
    Will lastWill = Util::getLastWillFor(objectID, instanceID);

    network = new Network(wifiLink, clientID, *mqtt, firstWill, lastWill);
  }

  void CBlocksMaker::setUpAudioPairing(){
    adc->begin(SS);
    AstroMech::AstroMech* astroMech = new AstroMech::AstroMech(analogReadFP, MIC_PIN, false);
    pairing = new AudioPairing(PAIRING_MODE_PIN, wifiLink, astroMech);
  }

  CBlocks* CBlocksMaker::makeNoPairing(unsigned int objectID, unsigned int instanceID, String ssid, String password){ //TODO
    setUpNetwork(objectID, instanceID);
    setUpHardcodedPairing(ssid, password);

    return new CBlocks(objectID, instanceID, network, powerManager, pairing, statusLED);
  }

  void CBlocksMaker::setUpHardcodedPairing(String ssid, String password){
    pairing = new HardcodedPairing(ssid, password, wifiLink);
  }
}
