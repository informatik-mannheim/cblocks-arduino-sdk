#ifndef HARDCODED_PAIRING_H
#define HARDCODED_PAIRING_H

#include "Arduino.h"
#include "Pairing.h"
#include "WiFiLink.h"

namespace CBlocks{
  class HardcodedPairing: public Pairing{
    WiFiLink* wifiLink;
    Credentials credentials;

    void clearCredentials();
  public:
    HardcodedPairing(String ssid, String password, WiFiLink* wifiLink);
    virtual void begin();
    virtual bool isPaired();
    virtual bool isPairingButtonOn();
    virtual bool pair();
    virtual void reset();
  };
}

#endif
