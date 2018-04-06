#include "StatusLED.h"
#include "Arduino.h"

namespace CBlocks{
  StatusLED::StatusLED(int redPin, int greenPin) : redPin(redPin), greenPin(greenPin){
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
  }

  void StatusLED::connecting(){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
  }

  void StatusLED::running(){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  void StatusLED::error(){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
}
