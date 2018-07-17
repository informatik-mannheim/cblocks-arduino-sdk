#include "Pairing.h"

namespace CBlocks{
  Pairing::Pairing(){
    getCredentials();
  }

  bool Pairing::isPaired(){
    return (credentials.ssid.length() && credentials.password.length());
  }

  bool Pairing::pair(){
    //TODO: Do the real stuff
    credentials = {"cblocks-gateway", "naeheaufdistanz"};
    EEPROM.put(EE_ADDRESS, credentials);

    return true;
  }

  Credentials Pairing::getCredentials(){
    EEPROM.get(EE_ADDRESS, credentials);
    return credentials;
  }
}
