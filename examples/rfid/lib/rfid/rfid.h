#ifndef RFID
#define RFID

#include "Arduino.h"
#include "CBlocks.h"
#include <SPI.h>
#include <MFRC522.h>

#define LAST_SUCCESSFULLL_READ_TIMEOUT 500
#define CARD_PRESENT_RESOURCE_ID 0
#define BUZZ_LENTH_IN_MS 300

namespace CBlocks{
  class CardReader{
  private:
    MFRC522* reader;
    CBlocks* cblocks;
    MFRC522::Uid card;
    long lastSuccessfullReadMillis;
    int buzzerPin;

    void readCard();
    void updateCardPresentResource();
    bool newCardPresent();
    void buzz();
    void resetCard();
    bool isCardPresent();
    bool isReadTimedOut();
  public:
    CardReader(MFRC522* reader, CBlocks* cblocks, int buzzerPin);
    void begin();
    void publishStatus();
  };

  CardReader::CardReader(MFRC522* reader, CBlocks* cblocks, int buzzerPin){
    this->reader = reader;
    this->cblocks = cblocks;
    this->lastSuccessfullReadMillis = 0;
    this->buzzerPin = buzzerPin;
  }

  void CardReader::begin(){
    SPI.begin();
    reader->PCD_Init();
    pinMode(buzzerPin, OUTPUT);
  }

  void CardReader::publishStatus(){
    this->cblocks->heartBeat();

    if(this->newCardPresent()){
      this->buzz();
      this->readCard();
      this->updateCardPresentResource();
    }
  }

  bool CardReader::newCardPresent(){
    if (this->isCardPresent()) {
      MFRC522::Uid newCard = this->reader->uid;
      for (size_t i = 0; i < newCard.size; i++) {
        if(newCard.uidByte[i] != this->card.uidByte[i]){
          return true;
        }
      }
  	}else{
      this->resetCard();
    }

  	return false;
  }

  bool CardReader::isCardPresent(){
    if (this->reader->PICC_IsNewCardPresent() && this->reader->PICC_ReadCardSerial()){
      this->lastSuccessfullReadMillis = millis();
      return true;
    }

    if(this->isReadTimedOut()){
      return false;
    }

    return true;
  }

  bool CardReader::isReadTimedOut(){
    return (millis() - this->lastSuccessfullReadMillis) > LAST_SUCCESSFULLL_READ_TIMEOUT;
  }

  void CardReader::resetCard(){
    for (size_t i = 0; i < 10; i++) {
      this->card.uidByte[i] = 0;
    }
  }

  void CardReader::buzz(){
    tone(buzzerPin, 800, BUZZ_LENTH_IN_MS);
  }

  void CardReader::readCard(){
    this->card = reader->uid;
  }

  void CardReader::updateCardPresentResource(){
    String cardSerialHex;

    for (size_t i = 0; i < this->card.size; i++) {
      cardSerialHex.concat(String(this->card.uidByte[i], 16));
    }

    this->cblocks->updateResource(CARD_PRESENT_RESOURCE_ID, cardSerialHex);
  }
}

#endif
