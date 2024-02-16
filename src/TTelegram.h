#ifndef ESP8266_BASE_V2_TTELEGRAM_H_
#define ESP8266_BASE_V2_TTELEGRAM_H_

#include <Arduino.h>
#include <AsyncTelegram2.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>

#include "../include/version.h"
#include "common.h"

// main.h
extern TPins pins;

class TTelegram {
 public:
  TTelegram() : certificate(telegram_cert), myBot(client){};

  void begin(String token, int64_t adminChatId, String boardName);
  void sendMessage(String message);
  void checkMessages();

 private:
  BearSSL::WiFiClientSecure client;
  BearSSL::Session session;
  BearSSL::X509List certificate;
  AsyncTelegram2 myBot;
  String token;
  int64_t adminChatId;
  String boardName;

  void commandPin(String message);
  void commandHelp();
  void commandSensors();
};

#endif  // ESP8266_BASE_V2_TTELEGRAM_H_