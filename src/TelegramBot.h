#ifndef ESP8266_BASE_V2_TELEGRAM_H_
#define ESP8266_BASE_V2_TELEGRAM_H_

#include <Arduino.h>
#include <AsyncTelegram2.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>

#include "common.h"
#include "../include/version.h"

class TelegramBot {
 private:
  BearSSL::WiFiClientSecure client;
  BearSSL::Session session;
  BearSSL::X509List certificate;
  AsyncTelegram2 myBot;
  String token;
  int64_t adminChatId;
  String boardName;

 public:
  TelegramBot() : certificate(telegram_cert), myBot(client){};

  void init(String token, int64_t adminChatId, String boardName);
  void sendMessage(String message);
  void checkMessages();
};

#endif  // ESP8266_BASE_V2_TELEGRAM_H_