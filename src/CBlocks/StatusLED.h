#ifndef CBLOCKS_STATUS_LED
#define CBLOCKS_STATUS_LED

#define HIGH_VALUE 100

namespace CBlocks{
  class StatusLED{
  private:
    int redPin;
    int greenPin;

  public:
    StatusLED(int redPin, int greenPin);
    void connecting();
    void running();
    void error();
  };
}

#endif
