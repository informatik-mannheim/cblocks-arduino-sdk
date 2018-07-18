#ifndef PAIRING_H
#define PAIRING_H

#include "Arduino.h"
#include "WiFiLink.h"
#include "UpdateTimer.h"
#include "AstroMac.h"

namespace CBlocks{
  class Pairing{
    static const int EE_ADDRESS = 0;
    static const long DEBOUNCE_MS = 20;
    int pairingModePin;
    bool lastButtonState;
    bool isPairingMode;
    bool isPairingStarted;
    WiFiLink* wifiLink;
    Credentials credentials;
    UpdateTimer* debounceUpdateTimer;
    AstroMac::AstroMac* astroMac;

    void clearCredentials();
  public:
    Pairing(int pairingModePin, WiFiLink* wifiLink, AstroMac::AstroMac* astroMac);
    void begin();
    bool isPaired();
    bool isInPairingMode();
    bool pair();
    void saveCredentials();
    void setLinkCredentials();
    void readCredentials();
  };
}

#endif
