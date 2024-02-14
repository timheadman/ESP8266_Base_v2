#ifndef ESP8266_BASE_V2_TELEGRAM_H_
#define ESP8266_BASE_V2_TELEGRAM_H_

#include <Arduino.h>
#include <AsyncTelegram2.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>

#include "Configuration.h"
#include "common.h"
#include "version.h"

// main.h
extern String mac;
// config.h
extern Configuration config;
// main.h
extern struct tm timeStructureNow;

class TelegramBot {
 private:
  BearSSL::WiFiClientSecure client;
  BearSSL::Session session;
  BearSSL::X509List certificate;
  AsyncTelegram2 myBot;

 public:
  TelegramBot();

  void init();
  void sendMessage(String message);
  void update();
};

#endif  // ESP8266_BASE_V2_TELEGRAM_H_