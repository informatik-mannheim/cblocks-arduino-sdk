#include "WiFi.h"
#include "Arduino.h"
#include "WiFiLink.h"

namespace CBlocks{
  // TODO inject wifi client
  WiFiLink::WiFiLink(){
    connectTimeoutUpdateTimer = new UpdateTimer(CONNECT_TIMEOUT_MS);
  }

  bool WiFiLink::connect(){
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(credentials.ssid);
    Serial.print("With password ");
    Serial.println(credentials.password);

    WiFi.begin(credentials.ssid.c_str(), credentials.password.c_str());
    connectTimeoutUpdateTimer->updateIntervalExceeded();

    while(WiFi.status() != WL_CONNECTED && !connectTimeoutUpdateTimer->updateIntervalExceeded()){
      Serial.print(".");
      delay(50);
    }

    if(WiFi.status() == WL_CONNECTED){
      randomSeed(micros());

      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());

      return true;
    }

    return false;
  }

  bool WiFiLink::isConnected(){
    return (WiFi.status() == WL_CONNECTED);
  }

  void WiFiLink::disconnect(){
    WiFi.disconnect();
  }

  void WiFiLink::setCredentials(Credentials credentials){
    this->credentials = credentials;
  }
}
