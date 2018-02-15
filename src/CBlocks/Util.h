#ifndef ARDUINO_H
#define ARDUINO_H

#include "Arduino.h"

class Util{
public:
  static const char* getClientID(unsigned int objectID, unsigned instanceID);
  static const char* getOutputTopic(unsigned int objectID, unsigned instanceID, int resourceID);
  static const char* getInputTopic(unsigned int objectID, unsigned instanceID, int resourceID);
};

#endif
