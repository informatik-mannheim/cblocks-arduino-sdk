#include "Arduino.h"
#include "AstroMac.h"
#include "Pairing.h"
#include "UpdateTimer.h"
#include "EEPROM.h"

namespace CBlocks{
  Pairing::Pairing(int pairingModePin, WiFiLink* wifiLink, AstroMac::AstroMac* astroMac)
  : pairingModePin(pairingModePin), wifiLink(wifiLink), astroMac(astroMac){
    isPairingMode = false;
    isPairingStarted = false;
    lastButtonState = HIGH;
    debounceUpdateTimer = new UpdateTimer(DEBOUNCE_MS);
  }

  void Pairing::begin(){
    if(!EEPROM.begin(100)){
      Serial.println("Failed to initialise EEPROM");
    }else{
      Serial.println("EEPROM initialized");
    }

    readCredentials();
    pinMode(pairingModePin, INPUT_PULLUP);

    if(isPaired()){
      setLinkCredentials();
    }
  }

  bool Pairing::isPaired(){
    Serial.println(credentials.ssid);
    Serial.println(credentials.password);
    return (credentials.ssid.length() && credentials.password.length());
  }

  bool Pairing::isInPairingMode(){
    if(debounceUpdateTimer->updateIntervalExceeded()){
      bool buttonState = digitalRead(pairingModePin);

      if(buttonState == LOW && lastButtonState == HIGH){
        isPairingMode = !isPairingMode;
      }

      lastButtonState = buttonState;
    }

    if(!isPairingMode){
      isPairingStarted = false;
    }

    return isPairingMode;
  }

  bool Pairing::pair(){
    if(!isPairingStarted){
      isPairingStarted = true;
      clearCredentials();
      setLinkCredentials();
    }

    String data = astroMac->detect(); //TODO extra function

    if(data.length()){
      credentials.ssid = String("cblocks-gateway");
      credentials.password = data;

      saveCredentials();
      setLinkCredentials();

      Serial.println(data);
      isPairingStarted = false;
      isPairingMode = false;
      return true;
    }

    return false;

  }

  void Pairing::clearCredentials(){
    credentials = {"",""};

    int bytes[100];
    EEPROM.writeBytes(EE_ADDRESS, bytes, 100);
    EEPROM.commit();
  }

  void Pairing::setLinkCredentials(){
    wifiLink->setCredentials(credentials);
  }

  void Pairing::saveCredentials(){
    EEPROM.writeString(EE_ADDRESS, credentials.ssid);
    EEPROM.writeString(EE_ADDRESS+40, credentials.password);
    EEPROM.commit();
  }

  void Pairing::readCredentials(){
    credentials.ssid = EEPROM.readString(EE_ADDRESS);
    credentials.password = EEPROM.readString(EE_ADDRESS+40);
    credentials.password.remove(credentials.password.length()-1);
  }
}
