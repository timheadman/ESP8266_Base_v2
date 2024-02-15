#ifndef ESP8266_BASE_V2_COMMON_H_
#define ESP8266_BASE_V2_COMMON_H_

#include <Arduino.h>

uint32_t getOnlineTime();
tm getTimeStructure();
String getTimeString();

#endif  // ESP8266_BASE_V2_COMMON_H_