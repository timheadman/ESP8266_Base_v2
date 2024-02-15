#include "main.h"
// AP IP address: 192.168.4.1, set manual IP in network settings.
GTimer timerOneSecond(MS);
struct tm timeStructureNow;
TConfiguration config;
TTelegram telegram;
Pins pins;

// **************************************************
// ********************* SETUP **********************
// **************************************************
void setup() {
  Serial.begin(115200);

  pinMode(D4, OUTPUT);

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
      Serial.printf(" [OK]\n*NTP: %s", getTimeString().c_str());
      break;
    }
  }

  telegram.init(config.getBotToken(), config.getAdminChatId(),
                config.getBoardName());
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
  loadPins();
  telegram.checkMessages();
  digitalWrite(D4, digitalRead(D4));
}

/**
 * Блок заполнения состояния пинов.
 */
void loadPins() {
  pins.d4 = digitalRead(D4);
  pins.d5 = digitalRead(D5);
  pins.d6 = digitalRead(D6);
  pins.d7 = digitalRead(D7);
  pins.d8 = digitalRead(D8);
}