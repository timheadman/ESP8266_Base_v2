#include "main.h"
// AP IP address: 192.168.4.1, set manual IP in network settings.
GTimer timerOneSecond(MS);
struct tm timeStructureNow;

void setup() {
  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.setTimeout(60);
  wifiManager.autoConnect();

  configTime("MSK-3", 0, "pool.ntp.org");
  timerOneSecond.setInterval(1000);

  Configuration config;
  // Инициализация файловой системы и загрузка конфигурации из файла
  if (LittleFS.begin()) {
    config.loadConfiguration();
    config.printConfiguration();
  } else {
    Serial.println(F("*FS: An Error has occurred while mounting LittleFS."));
  }
}

void loop() {
  if (timerOneSecond.isReady()) triggerOneSecond();
}

/**
 * Блок инструкций для запуска раз в секунду.
 */
void triggerOneSecond() {
  updateTime();
  if (time(nullptr) > 1700000000)
    Serial.printf("%lld (%d:%d:%d)\n", time(nullptr), timeStructureNow.tm_hour,
                  timeStructureNow.tm_min, timeStructureNow.tm_sec);
  else
    Serial.printf("*NTP: Synchronization failed.\n");
}

/**
 * Обновление структуры хранящую текущее время.
 */
void updateTime() {
  time_t unixTimeNow;
  time(&unixTimeNow);
  localtime_r(&unixTimeNow, &timeStructureNow);
}
