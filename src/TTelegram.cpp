#include "TTelegram.h"

void TTelegram::init(String token, int64_t adminChatId, String boardName) {
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
    } else if (message == "/sensors") {
      commandSensors();
    } else if (message.substring(0, 4) == "/pin") {
      commandPin(message);
    } else {
      sendMessage("Message: " + message);
    }
  }
}

void TTelegram::commandPin(String message) {
  sendMessage("D4:" + String(pins.d4) + " D5:" + String(pins.d5) +
              " D6:" + String(pins.d6) + " D7:" + String(pins.d7) +
              " D8:" + String(pins.d8));
}

void TTelegram::commandHelp() {
  time_t timeDiff = getOnlineTime();
  uint16_t hour = timeDiff / 3600;
  uint8_t min = (timeDiff / 60) % 60;
  uint8_t sec = timeDiff % 60;
  String strTimeDiff = String(hour) + " hours " + String(min) + " minutes " +
                       String(sec) + " seconds.";
  sendMessage("\nOnline: " + strTimeDiff);
}

void TTelegram::commandSensors() { sendMessage("Sensors: "); }
