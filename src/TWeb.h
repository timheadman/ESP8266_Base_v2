#ifndef ESP8266_BASE_V2_TWEB_H_
#define ESP8266_BASE_V2_TWEB_H_

#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

#include "common.h"

class TWeb {
 public:
  TWeb();
  TWeb(String boardName);

  void initWebServer();
  void notFound(AsyncWebServerRequest *request);
  static String processingPlaceHolder(AsyncWebServerRequest *request, const String &var);
  String getPinStringStatus(uint8_t pin);

 private:
  AsyncWebServer server;
  String boardName;
};

#endif  // ESP8266_BASE_V2_TWEB_H_