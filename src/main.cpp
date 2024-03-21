#include "main.h"

// AP IP address: 192.168.4.1, set manual IP in network settings.
GTimer timerOneSecond(MS);
struct tm timeStructureNow;
TConfiguration config;
TTelegram telegram;
TWeb web;
TNtc ntc = TNtc(A0);
TTime timeNow;

// **************************************************
// ********************* SETUP **********************
// **************************************************
void setup() {
  Serial.begin(115200);

  TPin::initPins();

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
      Serial.printf(" [OK]\n*NTP: %s", timeNow.getTimeString().c_str());
      break;
    }
  }

  telegram.begin(config.getBotToken(), config.getAdminChatId(),
                 config.getBoardName());

  web.begin();
}

// **************************************************
// ********************* LOOP ***********************
// **************************************************
void loop() {
  if (timerOneSecond.isReady()) triggerOneSecond();
}

/**
 * Блок инструкций для запуска раз в секунду.
 */
void triggerOneSecond() {
  Serial.printf("%.1f - %.1f\n", ntc.getTemperature(), ntc.getTemperatureB());
  telegram.checkMessages();
  // digitalWrite(D4, !digitalRead(D4));
}
