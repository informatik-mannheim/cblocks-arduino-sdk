#ifndef AUDIO_PAIRING_H
#define AUDIO_PAIRING_H

#include "Arduino.h"
#include "Pairing.h"
#include "WiFiLink.h"
#include "UpdateTimer.h"
#include "AstroMech.h"

namespace CBlocks{
  class AudioPairing: public Pairing{
    static const int EE_ADDRESS = 0;
    static const long DEBOUNCE_MS = 20;
    int pairingModePin;
    bool lastButtonState;
    WiFiLink* wifiLink;
    Credentials credentials;
    UpdateTimer* debounceUpdateTimer;
    AstroMech::AstroMech* astroMech;

    void clearCredentials();
  public:
    AudioPairing(int pairingModePin, WiFiLink* wifiLink, AstroMech::AstroMech* astroMech);
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
