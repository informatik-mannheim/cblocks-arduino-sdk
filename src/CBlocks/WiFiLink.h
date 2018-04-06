#ifndef CBLOCKS_WIFILINK
#define CBLOCKS_WIFILINK

#include "Link.h"
#include "Arduino.h"
#include "StatusLED.h"

namespace CBlocks{
  class WiFiLink: public Link{
  private:
    String ssid;
    String password;
  public:
    WiFiLink(String ssid, String password);
    virtual void connect();
  };
}

#endif
