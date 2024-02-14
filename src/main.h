#ifndef ESP8266_WIFI_BASE_H_
#define ESP8266_WIFI_BASE_H_

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <GyverTimer.h>
#include <WiFiManager.h>

void updateTime();
void triggerOneSecond();

#endif  // ESP8266_WIFI_BASE_H_