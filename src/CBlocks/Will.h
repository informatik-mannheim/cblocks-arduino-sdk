#ifndef WILL_H
#define WILL_H
  #include "Arduino.h"

  struct Will{
    String topic;
    int qos;
    bool retain;
    String message;
  };

#endif
