#ifndef AUDIO_TAG_H
#define AUDIO_TAG_H

#include "arduinoFFT.h"
#include "Decoder.h"

#define NUMBER_OF_SAMPLES 128
#define SAMPLING_FREQUENCY 12000
#define DATA_PERIOD_IN_MILLISECONS 50
#define TIMEOUT_IN_MS 200

#define START_FREQUENCY 600
#define FREQUENCY_STEP_SIZE 150
#define FREQUENCY_RANGE 60
#define START_SYMBOL_FREQUENCY 4500
#define STOP_SYMBOL_FREQUENCY 5000
#define DELIMTER_SYMBOL_FREQUENCY 4000
#define AMPLITUDE_THRESHOLD 200
#define DELIMITER_SYMBOL_INDEX 16
#define DELIMITER_SYMBOL 0xff

namespace AstroMac{
  typedef int (*AnalogReadFPT)(uint8_t pin); //TODO: use in constructor

  class AstroMac{
  private:
    uint16_t frequencies[17];
    uint8_t symbols[17] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, DELIMITER_SYMBOL};
    double realValues[NUMBER_OF_SAMPLES];
    double imaginaryValues[NUMBER_OF_SAMPLES];
    unsigned int sampling_period_us;
    arduinoFFT fft;
    unsigned long lastDataTickInMS;
    unsigned long lastSymbolReceivedInMS;
    Decoder *decoder;
    AnalogReadFPT analogReadFP;
    int analogPin;

    void initFrequencies();
    void sample();
    void addSymbol();
    void waitForNextSampleTick(unsigned long lastMicroseconds);
    bool isStartDetected();
    bool isStopOrTimeoutDetected();
    void waitForNextDataTick();
    int getSymbol();
    uint16_t getDominantFrequency();
    uint16_t getAmplitudeForFrequency(uint16_t frequency);
    uint8_t getBinForFrequency(uint16_t frequency);
  public:
    AstroMac(AnalogReadFPT analogReadFP, int analogPin);
    String detect();
  };
}

#endif
