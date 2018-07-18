#ifndef CBLOCKS_WIFILINK
#define CBLOCKS_WIFILINK

#include "Link.h"
#include "Arduino.h"
#include "UpdateTimer.h"

namespace CBlocks{
  struct Credentials {
    String ssid;
    String password;
  };

  class WiFiLink: public Link{
  private:
    const long CONNECT_TIMEOUT_MS = 3000;
    Credentials credentials;
    UpdateTimer* connectTimeoutUpdateTimer;
  public:
    WiFiLink();
    virtual bool connect();
    virtual bool isConnected();
    virtual void disconnect();
    void setCredentials(Credentials credentials);
  };
}

#endif
