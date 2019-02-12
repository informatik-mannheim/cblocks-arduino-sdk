#ifndef PAIRING_H
#define PAIRING_H

#include "Arduino.h"

namespace CBlocks{
  class Pairing{
  public:
    virtual void begin();
    virtual bool isPaired();
    virtual bool isPairingButtonOn();
    virtual bool pair();
    virtual void reset();
  };
}

#endif
