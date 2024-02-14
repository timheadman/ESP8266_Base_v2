#include "telegram.h"

#define USE_CLIENTSSL true
#include <ESP8266WiFi.h>
#include <time.h>
BearSSL::WiFiClientSecure clientTg;
BearSSL::Session sessionTg;
BearSSL::X509List certificateTg(telegram_cert);

AsyncTelegram2 myBot(clientTg);

void initTelegram() {
  // Sync time with NTP, to check properly Telegram certificate
  // Set certficate, session and some other base client properies
  clientTg.setSession(&sessionTg);
  clientTg.setTrustAnchors(&certificateTg);
  clientTg.setBufferSizes(1024, 1024);

  Serial.print(F("*TGM: Test Telegram connection... "));
  // Set the Telegram bot properies
  myBot.setUpdateTime(2000);
  myBot.setTelegramToken(config.getBotToken().c_str());
  myBot.begin() ? Serial.println("[OK]") : Serial.println("[FAIL]");
  sendTelegramMessage("Запуск модуля.");
}

void sendTelegramMessage(String message) {
  myBot.sendTo(config.getAdminChatId(),
               message + "\n" + String(asctime(&timeStructureNow)) + "ID: " + mac +
                   " (" + config.getBoardName() + ")" +
                   "\nSSID: " + String(config.getSsid()) +
                   " IP: " + WiFi.localIP().toString() + "\nv." + VERSION +
                   " (" + BUILD_TIMESTAMP + ")");
}

void getTelegramUpdate() {
  TBMessage msg;
  if (myBot.getNewMessage(msg)) {
    String message = msg.text;
    Serial.print("*TGM: Telegram Chat ID - " + String(msg.chatId) + " (" +
                 String(msg.contact.firstName) +
                 "). New message: " + String(message) + "\n");
    if (message == "/help") {
      time_t timeDiff = getOnlineTime();
      uint16_t hour = timeDiff / 3600;
      uint8_t min = (timeDiff / 60) % 60;
      uint8_t sec = timeDiff % 60;
      String strTimeDiff = String(hour) + " часов " + String(min) + " минут " +
                           String(sec) + " секунд.";
      sendTelegramMessage("\nОнлайн: " + strTimeDiff);
    } else if (message == "/sensors") {
      sendTelegramMessage("Sensors: ");
    } else {
      sendTelegramMessage("Получено сообщение: " + message);
    }
  }
}