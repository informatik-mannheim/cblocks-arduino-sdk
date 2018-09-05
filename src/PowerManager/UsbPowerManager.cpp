#include "Arduino.h"
#include "UsbPowerManager.h"

namespace CBlocks{
  UsbPowerManager::UsbPowerManager(){};

  void UsbPowerManager::begin(){
  }

  void UsbPowerManager::turnOn(){
  }

  bool UsbPowerManager::isPowerButtonOn(){
    return true;
  }

  bool UsbPowerManager::isBatteryLow(){
    return false;
  }

  void UsbPowerManager::turnOff(){
  }

  BatteryStatus UsbPowerManager::getBatteryStatus(){
    return high;
  }
}
