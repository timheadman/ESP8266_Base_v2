#include "TelegramBot.h"

TelegramBot::TelegramBot() : certificate(telegram_cert), myBot(client) {}

void TelegramBot::init() {
  client.setSession(&session);
  client.setTrustAnchors(&certificate);
  client.setBufferSizes(1024, 1024);

  Serial.print(F("*TGM: Test Telegram connection... "));

  myBot.setUpdateTime(2000);
  myBot.setTelegramToken(config.getBotToken().c_str());
  myBot.begin() ? Serial.println("[OK]") : Serial.println("[FAIL]");

  sendMessage("Модуль запущен.");
}

void TelegramBot::sendMessage(String message) {
  myBot.sendTo(config.getAdminChatId(),
               message + "\n" + String(asctime(&timeStructureNow)) +
                   "ID: " + mac + " (" + config.getBoardName() + ")" +
                   " IP: " + WiFi.localIP().toString() + "\nv." + VERSION +
                   " (" + BUILD_TIMESTAMP + ")");
}

void TelegramBot::update() {
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
      sendMessage("\nОнлайн: " + strTimeDiff);
    } else if (message == "/sensors") {
      sendMessage("Sensors: ");
    } else {
      sendMessage("Получено сообщение: " + message);
    }
  }
}