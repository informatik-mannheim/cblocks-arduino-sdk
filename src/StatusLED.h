#ifndef CBLOCKS_STATUS_LED
#define CBLOCKS_STATUS_LED

#define HIGH_VALUE 60

#include <Adafruit_NeoPixel.h>

namespace CBlocks{
  class StatusLED{
  private:
    Adafruit_NeoPixel* strip;
    int statusPixel;
    void clear();

  public:
    StatusLED(Adafruit_NeoPixel* strip, int statusPixel);
    void connecting();
    void running();
    void error();
    void pairing();
  };
}

#endif
