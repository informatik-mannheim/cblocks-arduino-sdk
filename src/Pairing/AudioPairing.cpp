#ifdef AURDIO_PAIRING

#include "Arduino.h"
#include "AstroMac.h"
#include "AudioPairing.h"
#include "UpdateTimer.h"
#include "EEPROM.h"

namespace CBlocks{
  AudioPairing::AudioPairing(int pairingModePin, WiFiLink* wifiLink, AstroMac::AstroMac* astroMac)
  : pairingModePin(pairingModePin), wifiLink(wifiLink), astroMac(astroMac){
    lastButtonState = HIGH;
    debounceUpdateTimer = new UpdateTimer(DEBOUNCE_MS);
  }

  void AudioPairing::begin(){
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

  bool AudioPairing::isPaired(){
    return (credentials.ssid.length() && credentials.password.length());
  }

  bool AudioPairing::isPairingButtonOn(){
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

  void AudioPairing::reset(){
    clearCredentials();
    setLinkCredentials();
  }

  bool AudioPairing::pair(){
    String data = astroMac->detect(); //TODO extra function

    if(data.length() && data.indexOf(';')){
      credentials.ssid = data.substring(0, data.indexOf(';'));
      credentials.password = data.substring(data.indexOf(';')+1);

      saveCredentials();
      setLinkCredentials();

      return true;
    }

    return false;

  }

  void AudioPairing::clearCredentials(){
    credentials = {"",""};

    int bytes[100];
    EEPROM.writeBytes(EE_ADDRESS, bytes, 100);
    EEPROM.commit();
  }

  void AudioPairing::setLinkCredentials(){
    wifiLink->setCredentials(credentials);
  }

  void AudioPairing::saveCredentials(){
    EEPROM.writeString(EE_ADDRESS, credentials.ssid);
    EEPROM.writeString(EE_ADDRESS+40, credentials.password);
    EEPROM.commit();
  }

  void AudioPairing::readCredentials(){
    credentials.ssid = EEPROM.readString(EE_ADDRESS);
    credentials.password = EEPROM.readString(EE_ADDRESS+40);
    credentials.password.remove(credentials.password.length()-1);
  }
}

#endif
