#include "StatusLED.h"
#include "Arduino.h"

namespace CBlocks{
  StatusLED::StatusLED(int redPin, int greenPin) : redPin(redPin), greenPin(greenPin){
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
  }

  void StatusLED::connecting(){
    analogWrite(redPin, HIGH_VALUE);
    analogWrite(greenPin, HIGH_VALUE);
  }

  void StatusLED::running(){
    analogWrite(redPin, LOW);
    analogWrite(greenPin, HIGH_VALUE);
  }

  void StatusLED::error(){
    analogWrite(redPin, HIGH_VALUE);
    analogWrite(greenPin, LOW);
  }
}
