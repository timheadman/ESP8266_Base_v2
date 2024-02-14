#ifndef ESP8266_BASE_V2_TELEGRAM_H_
#define ESP8266_BASE_V2_TELEGRAM_H_

#include <Arduino.h>
#include <AsyncTelegram2.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "config.h"
#include "version.h"
#include "common.h"

// main.h
extern String mac;
// config.h
extern Configuration config;
// main.h
extern struct tm timeStructureNow;

void initTelegram();
void sendTelegramMessage(String message);
void getTelegramUpdate();

#endif  // ESP8266_BASE_V2_TELEGRAM_H_