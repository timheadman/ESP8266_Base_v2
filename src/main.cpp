#include "main.h"
// AP IP address: 192.168.4.1, set manual IP in network settings.
GTimer timerOneSecond(MS);
struct tm timeStructureNow;
Configuration config;
TelegramBot telegram;

void setup() {
  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.setTimeout(60);
  wifiManager.autoConnect();

  configTime("MSK-3", "time.google.com", "time.windows.com", "pool.ntp.org");
  timerOneSecond.setInterval(1000);

  if (LittleFS.begin()) {
    config.loadConfiguration();
    config.printConfiguration();
  } else {
    Serial.println(F("*FS: An Error has occurred while mounting LittleFS."));
  }

  Serial.printf("*NTP: Synchronization");
  for (int i = 0; i < 10; ++i) {
    if (time(nullptr) < 1700000000) {
      Serial.printf(".");
      delay(1000);
    } else {
      updateTime();
      Serial.printf(" [OK]\n*NTP: %s", asctime(&timeStructureNow));
      break;
    }
  }

  telegram.init(config.getBotToken(), config.getAdminChatId(),
                config.getBoardName());
}

void loop() {
  if (timerOneSecond.isReady()) triggerOneSecond();
    telegram.update();
}

/**
 * Блок инструкций для запуска раз в секунду.
 */
void triggerOneSecond() {
  updateTime();

}

/**
 * Обновление структуры хранящую текущее время.
 */
void updateTime() {
  time_t unixTimeNow;
  time(&unixTimeNow);
  localtime_r(&unixTimeNow, &timeStructureNow);
}
