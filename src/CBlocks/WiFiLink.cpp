#include "ESP8266WiFi.h"
#include "Arduino.h"
#include "WiFiLink.h"

namespace CBlocks{
  WiFiLink::WiFiLink(String ssid, String password){
    this->ssid = ssid;
    this->password = password;
  }

  void WiFiLink::connect(){
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid.c_str(), password.c_str());

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
}
