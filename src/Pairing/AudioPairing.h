#ifndef AUDIO_PAIRING_H
#define AUDIO_PAIRING_H

#include "Arduino.h"
#include "Pairing.h"
#include "WiFiLink.h"
#include "UpdateTimer.h"
#include "AstroMac.h"

namespace CBlocks{
  class AudioPairing: public Pairing{
    static const int EE_ADDRESS = 0;
    static const long DEBOUNCE_MS = 20;
    int pairingModePin;
    bool lastButtonState;
    WiFiLink* wifiLink;
    Credentials credentials;
    UpdateTimer* debounceUpdateTimer;
    AstroMac::AstroMac* astroMac;

    void clearCredentials();
  public:
    AudioPairing(int pairingModePin, WiFiLink* wifiLink, AstroMac::AstroMac* astroMac);
    virtual void begin();
    virtual bool isPaired();
    virtual bool isPairingButtonOn();
    virtual void reset();
    virtual bool pair();
    void saveCredentials();
    void setLinkCredentials();
    void readCredentials();
  };
}

#endif
