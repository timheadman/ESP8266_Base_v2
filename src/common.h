#ifndef ESP8266_BASE_V2_COMMON_H_
#define ESP8266_BASE_V2_COMMON_H_

#include <Arduino.h>

struct Pins {
  uint16_t d4;
  uint16_t d5;
  uint16_t d6;
  uint16_t d7;
  uint16_t d8;
};

uint32_t getOnlineTime();
tm getTimeStructure();
String getTimeString();

#endif  // ESP8266_BASE_V2_COMMON_H_