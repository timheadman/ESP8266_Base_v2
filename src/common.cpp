#include "common.h"
/**
 * Вывод состояния всех пинов в строку.
 */
String getPinsStatusString() {
  return "[A0:" + String(analogRead(A0)) + "] [D1:" + String(digitalRead(D1)) +
         ", D2:" + String(digitalRead(D2)) + ", D3:" + String(digitalRead(D3)) +
         ", D4:" + String(digitalRead(D4)) + ", D5:" + String(digitalRead(D5)) +
         ", D6:" + String(digitalRead(D6)) + ", D7:" + String(digitalRead(D7)) +
         ", D8:" + String(digitalRead(D8)) + "]";
}