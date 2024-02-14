#include "main.h"
// AP IP address: 192.168.4.1, set manual IP in network settings.
GTimer timerOneSecond(MS);
struct tm timeStructureNow;
Configuration config;
TelegramBot telegram;
String mac = WiFi.macAddress();

void setup() {
  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.setTimeout(60);
  wifiManager.autoConnect();

  configTime("MSK-3", "time.google.com", "time.windows.com", "pool.ntp.org");
  timerOneSecond.setInterval(1000);

  // Инициализация файловой системы и загрузка конфигурации из файла
  if (LittleFS.begin()) {
    config.loadConfiguration();
    config.printConfiguration();
  } else {
    Serial.println(F("*FS: An Error has occurred while mounting LittleFS."));
  }

  while (time(nullptr) < 1700000000) {
    Serial.printf("*NTP: Synchronization failed.\n");
    delay(1000);
  }

  updateTime();
  Serial.print("*NTP: ");
  Serial.println(getTimeString());
  telegram.init();
}

void loop() {
  if (timerOneSecond.isReady()) triggerOneSecond();
}

/**
 * Блок инструкций для запуска раз в секунду.
 */
void triggerOneSecond() {
  updateTime();
  telegram.update();
}

/**
 * Обновление структуры хранящую текущее время.
 */
void updateTime() {
  time_t unixTimeNow;
  time(&unixTimeNow);
  localtime_r(&unixTimeNow, &timeStructureNow);
}

/**
 * Получение строки с текущими датой и временем.
 */
String getTimeString() {
  char buffer[80];
  strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeStructureNow);
  return String(buffer);
}
