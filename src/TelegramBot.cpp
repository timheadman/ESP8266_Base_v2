#include "TelegramBot.h"

void TelegramBot::init(String token, int64_t adminChatId, String boardName) {
  this->token = token;
  this->adminChatId = adminChatId;
  this->boardName = boardName;
  client.setSession(&session);
  client.setTrustAnchors(&certificate);
  client.setBufferSizes(1024, 1024);

  Serial.print(F("*TGM: Test Telegram connection... "));

  myBot.setUpdateTime(2000);
  myBot.setTelegramToken(token.c_str());
  myBot.begin() ? Serial.println("[OK]") : Serial.println("[FAIL]");

  sendMessage("Модуль запущен.");
}

void TelegramBot::sendMessage(String message) {
  String boardNameLocal = (boardName == "") ? "" : boardName + "\n";
  myBot.sendTo(adminChatId, message + "\n----------\n" + boardNameLocal +
                                getTimeString() +
                                "MAC: " + WiFi.macAddress() +
                                "\nIP: " + WiFi.localIP().toString() + "\nv." +
                                VERSION + " (" + BUILD_TIMESTAMP + ")");
}

void TelegramBot::checkMessages() {
  TBMessage msg;
  Serial.print(myBot.getNewMessage(msg));
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
      String strTimeDiff = String(hour) + " hours " + String(min) +
                           " minutes " + String(sec) + " seconds.";
      sendMessage("\nOnline: " + strTimeDiff);
    } else if (message == "/sensors") {
      sendMessage("Sensors: ");
    } else {
      sendMessage("Message: " + message);
    }
  }
}