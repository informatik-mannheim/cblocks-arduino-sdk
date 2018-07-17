#ifndef PAIRING_H
#define PAIRING_H

#include "Arduino.h"
#include "EEPROM.h"

namespace CBlocks{
  struct Credentials {
    String ssid;
    String password;
  };

  class Pairing{
    static const int EE_ADDRESS = 0;
    Credentials credentials;
  public:
    Pairing();
    bool isPaired();
    bool pair();
    Credentials getCredentials();
  };
}

#endif
