#include "TWeb.h"

// TODO: Добавить настройки с редактированием имени контроллера.

/**
 * Запуск Web сервера
 * @param boardName имя контроллера (название прибора)
 */
void TWeb::begin() {
  Serial.print(F("*WEB: Server initializing "));
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/style.css", "text/css");
  });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/script.js", "text/JavaScript");
  });
  server.on("/time", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plane", timeNow.getTimeString());
  });
  server.on("/pins", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plane", getPinsStatusString());
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", String(), false, processor);
  });

  ElegantOTA.begin(&server);
  server.onNotFound(notFound);
  server.begin();
  Serial.println(F("[OK]"));
}

String TWeb::processor(const String &var) {
  if (var == "PH_1") return config.getBoardName();
  return String();
}

void TWeb::notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
