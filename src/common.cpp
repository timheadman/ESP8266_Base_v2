#include "common.h"
/**
 * Получить время работы модуля без перезагрузки.
 * @return Секунды (time_t).
 */
uint32_t getOnlineTime() {
  static uint32_t onlineTimeSec = 0;
  static uint32_t lastMillis = 0;
  uint32_t nowMillis = millis();
  onlineTimeSec += lastMillis < nowMillis
                       ? (nowMillis - lastMillis) / 1000
                       : (4294967295 - lastMillis + nowMillis) / 1000;
  lastMillis = nowMillis;
  return onlineTimeSec;
}

/**
 * Обновление структуры c текущим временем.
 */
tm getTimeStructure() {
  time_t unixTimeNow;
  tm timeStructureNow;
  time(&unixTimeNow);
  localtime_r(&unixTimeNow, &timeStructureNow);
  return timeStructureNow;
}

/**
 * Строка с текущим временем.
 */
String getTimeString() {
  time_t unixTimeNow;
  tm timeStructureNow;
  time(&unixTimeNow);
  localtime_r(&unixTimeNow, &timeStructureNow);
  return asctime(&timeStructureNow);
}