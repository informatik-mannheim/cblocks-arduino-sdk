#include "Arduino.h"
#include "HardcodedPairing.h"

namespace CBlocks{
  HardcodedPairing::HardcodedPairing(String ssid, String password, WiFiLink* wifiLink)
  : wifiLink(wifiLink){
    credentials = {ssid, password};
  }

  void HardcodedPairing::begin(){
    wifiLink->setCredentials(credentials);
  }

  bool HardcodedPairing::pair(){
    return true;
  }

  bool HardcodedPairing::isPaired(){
    return true;
  }

  bool HardcodedPairing::isPairingButtonOn(){
    return false;
  }

  void HardcodedPairing::reset(){

  }
}
