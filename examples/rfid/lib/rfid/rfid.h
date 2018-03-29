#ifndef RFID
#define RFID

#include "Arduino.h"
#include "CBlocks.h"
#include <SPI.h>
#include <MFRC522.h>

#define CARD_PRESENT_RESOURCE_ID 0

namespace RFID{
  class CardReader{
  private:
    MFRC522* reader;
    CBlocks* cblocks;
    MFRC522::Uid card;

    void readCard();
    void updateCardPresentResource();
    bool newCardPresent();
  public:
    CardReader(MFRC522* reader, CBlocks* cblocks);
    void begin();
    void publishStatus();
  };

  CardReader::CardReader(MFRC522* reader, CBlocks* cblocks){
    this->reader = reader;
    this->cblocks = cblocks;
  }

  void CardReader::begin(){
    SPI.begin();
    reader->PCD_Init();
  }

  void CardReader::publishStatus(){
    if(this->newCardPresent()){
      this->readCard();
      this->updateCardPresentResource();
    }
  }

  bool CardReader::newCardPresent(){
    //TODO: reset card when there  is no card present
    if ( this->reader->PICC_IsNewCardPresent()) {
      if ( this->reader->PICC_ReadCardSerial()) {
        MFRC522::Uid newCard = this->reader->uid;
        for (size_t i = 0; i < newCard.size; i++) {
          if(newCard.uidByte[i] != this->card.uidByte[i]){
            return true;
          }
        }
      }
  	}

  	return false;
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
