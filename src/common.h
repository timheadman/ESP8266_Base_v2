#ifndef ESP8266_BASE_V2_COMMON_H_
#define ESP8266_BASE_V2_COMMON_H_

class TPins {
 public:
  uint16_t getA0() const { return a0; }
  void setA0(const uint16_t &a0_) { a0 = a0_; }

  uint16_t getD1() const { return d1; }
  void setD1(const uint16_t &d1_) { d1 = d1_; }

  uint16_t getD2() const { return d2; }
  void setD2(const uint16_t &d2_) { d2 = d2_; }

  uint16_t getD3() const { return d3; }
  void setD3(const uint16_t &d3_) { d3 = d3_; }

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
    return "[A0:" + String(getA0()) + "] [D1:" + String(getD1()) +
           ", D2:" + String(getD2()) + ", D3:" + String(getD3()) +
           ", D4:" + String(getD4()) + ", D5:" + String(getD5()) +
           ", D6:" + String(getD6()) + ", D7:" + String(getD7()) +
           ", D8:" + String(getD8()) + "]";
  }

 private:
  uint16_t a0;
  uint16_t d1;
  uint16_t d2;
  uint16_t d3;
  uint16_t d4;
  uint16_t d5;
  uint16_t d6;
  uint16_t d7;
  uint16_t d8;
};

#endif  // ESP8266_BASE_V2_COMMON_H_