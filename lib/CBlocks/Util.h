#ifndef ARDUINO_H
#define ARDUINO_H

#include "Arduino.h"

class Util{
public:
  static const char* getOutputTopic(unsigned int objectID, unsigned instanceID, int resourceID);
};

#endif
