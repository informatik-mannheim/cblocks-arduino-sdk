#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Arduino.h"
#include "CBlocks.h"
#include "DHT_U.h"
#include "UpdateTimer.h"

#define TEMPERATURE_RESOURCE_ID 0
#define HUMIDITY_RESOURCE_ID 1
#define UPDATE_INTERVAL_IN_MS 1000

namespace CBlocks{
  class Room{
  private:
    DHT_Unified* dht;
    CBlocks* cblocks;
    float temperatureCelsius;
    float relativeHumidity;
    UpdateTimer* updateTimer;

    void publishTemperature();
    void readTemperature();
    void publishHumidity();
    void readHumidity();
  public:
    Room(DHT_Unified* dht, CBlocks* cblocks);

    void begin();
    void publishStatus();
  };

  Room::Room(DHT_Unified* dht, CBlocks* cblocks){
    this->dht = dht;
    this->cblocks = cblocks;
    this->updateTimer = new UpdateTimer(UPDATE_INTERVAL_IN_MS);
  }

  void Room::begin(){
    this->cblocks->heartBeat();
  }

  void Room::publishStatus(){
    if(updateTimer->updateIntervalExceeded()){
      this->publishTemperature();
      this->publishHumidity();
    }

    this->cblocks->heartBeat();
  }

  void Room::publishTemperature(){
      this->readTemperature();
      this->cblocks->updateResource(TEMPERATURE_RESOURCE_ID, this->temperatureCelsius);
  }

  void Room::readTemperature(){
    sensors_event_t event;
    this->dht->temperature().getEvent(&event);

    if (!isnan(event.temperature)) {
      this->temperatureCelsius = event.temperature;
    }
  }

  void Room::publishHumidity(){
      this->readHumidity();
      this->cblocks->updateResource(HUMIDITY_RESOURCE_ID, this->relativeHumidity);
  }

  void Room::readHumidity(){
    sensors_event_t event;
    this->dht->humidity().getEvent(&event);

    if (!isnan(event.relative_humidity)) {
      this->relativeHumidity = event.relative_humidity;
    }
  }
}


#endif
