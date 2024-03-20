#ifndef ESP8266_BASE_V2_TWEB_H_
#define ESP8266_BASE_V2_TWEB_H_

// https://github.com/esphome/ESPAsyncWebServer

#define WEBSERVER_H  // https://github.com/me-no-dev/ESPAsyncWebServer/issues/418#issuecomment-667976368

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h> 
#include <ElegantOTA.h>
#include <LittleFS.h>

#include "TConfiguration.h"
#include "TTime.h"
#include "common.h"

// main.h
extern TConfiguration config;
extern TTime timeNow;

class TWeb {
 public:
  TWeb() : server(80) {}

  void begin();

 private:
  AsyncWebServer server;

  static String processor(const String& var);
  static void notFound(AsyncWebServerRequest* request);
};

#endif  // ESP8266_BASE_V2_TWEB_H_