#ifndef ARDUINO_H
#define ARDUINO_H

#include "Arduino.h"

class Util{
public:
  static String getClientID(unsigned int objectID, unsigned instanceID);
  static String getOutputTopic(unsigned int objectID, unsigned instanceID, int resourceID);
  static String getInputTopic(unsigned int objectID, unsigned instanceID, int resourceID);
  static String getPayloadFor(unsigned int value);
};

#endif
