#ifndef ESP8266_BASE_V2_COMMON_H_
#define ESP8266_BASE_V2_COMMON_H_

#include <Arduino.h>

#include "common.h"

class TPins {
 public:
  uint16_t getD4() const { return d4; }
  void setD4(const uint16_t &d4_) { d4 = d4_; }

  uint16_t getD5() const { return d5; }
  void setD5(const uint16_t &d5_) { d5 = d5_; }

  uint16_t getD6() const { return d6; }
  void setD6(const uint16_t &d6_) { d6 = d6_; }

  uint16_t getD7() const { return d7; }
  void setD7(const uint16_t &d7_) { d7 = d7_; }

  uint16_t getD8() const { return d8; }
  void setD8(const uint16_t &d8_) { d8 = d8_; }

  String toString() {
    return "[" + String(getD4()) + ", " + String(getD5()) + ", " +
           String(getD6()) + ", " + String(getD7()) + ", " + String(getD8()) +
           "]";
  }

 private:
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