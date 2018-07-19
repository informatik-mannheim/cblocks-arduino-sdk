#include "Arduino.h"
#include "AstroMac.h"
#include "Pairing.h"
#include "UpdateTimer.h"
#include "EEPROM.h"

namespace CBlocks{
  Pairing::Pairing(int pairingModePin, WiFiLink* wifiLink, AstroMac::AstroMac* astroMac)
  : pairingModePin(pairingModePin), wifiLink(wifiLink), astroMac(astroMac){
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
    return (credentials.ssid.length() && credentials.password.length());
  }

  bool Pairing::isPairingButtonOn(){
    bool result = false;

    if(debounceUpdateTimer->updateIntervalExceeded()){
      bool buttonState = digitalRead(pairingModePin);

      if(buttonState == LOW && lastButtonState == HIGH){
        result = true;
      }

      lastButtonState = buttonState;
    }

    return result;
  }

  void Pairing::reset(){
    clearCredentials();
    setLinkCredentials();
  }

  bool Pairing::pair(){
    String data = astroMac->detect(); //TODO extra function

    if(data.length()){
      credentials.ssid = String("cblocks-gateway");
      credentials.password = data;

      saveCredentials();
      setLinkCredentials();

      Serial.println(data);
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
