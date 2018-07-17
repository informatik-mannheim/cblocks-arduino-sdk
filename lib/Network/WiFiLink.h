#ifndef CBLOCKS_WIFILINK
#define CBLOCKS_WIFILINK

#include "Link.h"
#include "Arduino.h"
#include "StatusLED.h"
#include "Pairing.h"

namespace CBlocks{
  class WiFiLink: public Link{
  private:
    Credentials credentials;
    Pairing* pairing;
  public:
    WiFiLink(Pairing* pairing);
    virtual void connect();
  };
}

#endif
