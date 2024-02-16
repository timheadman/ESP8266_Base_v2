#include "TTelegram.h"

void TTelegram::begin(String token, int64_t adminChatId, String boardName) {
  this->token = token;
  this->adminChatId = adminChatId;
  this->boardName = boardName;

  client.setSession(&session);
  client.setTrustAnchors(&certificate);
  client.setBufferSizes(1024, 1024);

  myBot.setUpdateTime(2000);
  myBot.setTelegramToken(this->token.c_str());

  Serial.print(F("*TGM: Test Telegram connection... "));
  myBot.begin() ? Serial.println("[OK]") : Serial.println("[FAIL]");
  sendMessage("Модуль запущен.");
}

void TTelegram::sendMessage(String message) {
  String boardNameLocal = (boardName == "") ? "" : boardName + "\n";
  myBot.sendTo(adminChatId, message + "\n----------\n" + boardNameLocal +
                                getTimeString() + "MAC: " + WiFi.macAddress() +
                                "\nIP: " + WiFi.localIP().toString() + "\nv." +
                                VERSION + " (" + BUILD_TIMESTAMP + ")");
}

/*
help - Description
pins - Another description
*/
void TTelegram::checkMessages() {
  TBMessage msg;
  MessageType msg_type = myBot.getNewMessage(msg);
  if (msg_type) {
    String message = msg.text;
    Serial.print("*TGM: Telegram Chat ID - " + String(msg.chatId) + " (" +
                 String(msg.contact.firstName) +
                 "). New message: " + String(message) + "\n");
    if (message == "/help") {
      commandHelp();
    } else if (message.substring(0, 5) == "/pins") {
      commandPins();
    } else {
      sendMessage("Message: " + message);
    }
  }
}

void TTelegram::commandPins() { sendMessage(pins.toString()); }

void TTelegram::commandHelp() {
  time_t timeDiff = getOnlineTime();
  uint16_t hour = timeDiff / 3600;
  uint8_t min = (timeDiff / 60) % 60;
  uint8_t sec = timeDiff % 60;
  String strTimeDiff = String(hour) + " hours " + String(min) + " minutes " +
                       String(sec) + " seconds.";
  sendMessage("\nOnline: " + strTimeDiff);
}
