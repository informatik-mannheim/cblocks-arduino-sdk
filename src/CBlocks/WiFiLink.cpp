#include "WiFi.h"
#include "Arduino.h"
#include "WiFiLink.h"
#include "Pairing.h"

namespace CBlocks{
  // TODO inject wifi client
  WiFiLink::WiFiLink(Pairing* pairing){
    this->pairing = pairing;
  }

  void WiFiLink::connect(){
    if(!pairing->isPaired()){
      // TODO pairing has to be done explicitly
      pairing->pair();

      this->credentials = pairing->getCredentials();
    }

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(credentials.ssid);
    Serial.print("With password ");
    Serial.println(credentials.password);

    WiFi.begin(credentials.ssid.c_str(), credentials.password.c_str());

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
