#include "main.h"
// AP IP address: 192.168.4.1, set manual IP in network settings.
GTimer timerOneSecond(MS);
struct tm timeStructureNow;
TConfiguration config;
TTelegram telegram;
TWeb web;
TPins pins;

// **************************************************
// ********************* SETUP **********************
// **************************************************
void setup() {
  Serial.begin(115200);

  // Выводы которые требуют наличия определенного логического уровня на момент
  // включения микроконтроллера.
  pinMode(D0, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);  // LED
  pinMode(D8, OUTPUT);

  // Выводы которые могут использоваться для получения сигнала.
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

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
  loadPins();
  telegram.checkMessages();
  digitalWrite(D4, !digitalRead(D4));
  Serial.println(pins.toString());
}

/**
 * Блок заполнения состояния пинов.
 */
void loadPins() {
  pins.setD4(digitalRead(D4));
  pins.setD5(digitalRead(D5));
  pins.setD6(digitalRead(D6));
  pins.setD7(digitalRead(D7));
  pins.setD8(digitalRead(D8));
}