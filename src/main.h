#ifndef ESP8266_BASE_V2_BASE_H_
#define ESP8266_BASE_V2_BASE_H_

#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <GyverTimer.h>
#include <WiFiManager.h>

#include "TConfiguration.h"
#include "TNtc.h"
#include "TPin.h"
#include "TTelegram.h"
#include "TTime.h"
#include "TWeb.h"

void triggerOneSecond();
void initPins();

#endif  // ESP8266_BASE_V2_BASE_H_