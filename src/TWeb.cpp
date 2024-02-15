#include "TWeb.h"

#include <AsyncElegantOTA.h>  // Не переносить в HEADER файл, кривая библиотека.

const char *headerPlaceHolder PROGMEM = R"=====(
<div style="font-size: 1.2rem; text-transform: uppercase; font-weight: bold;">%s</div>
<span id="time" style="font-style: italic">%s</span>
)=====";

const char *mainPlaceHolder PROGMEM = R"=====(
 <input type="text" id="input_1" style="text-align: center; width: 5rem; font-size: 1rem; font-weight: bold;" placeholder="VALUE"/>
 <button type="button" id="button3" onclick="processingButton(this)" style="margin-left: 1rem">SEND</button>
 <br><br>
 <h3>PIN %s</h3>
 <label class="switch"><input type="checkbox" onchange="toggleCheckbox(this)" id="switch%s" %s>
 <span class="slider"></span></label><h3>Enable button</h3><label class="switch">
 <input type="checkbox" onchange="showElement(button1, this.checked)" id="switchreset" ><span class="slider">
 </span></label>
 <br><br>
 <button type="button" id="button1" disabled="false" onclick="processingButton(this)">BUTTON1</button>
)=====";

TWeb::TWeb() : server(80), boardName(""){};
TWeb::TWeb(String boardName) : TWeb() { this->boardName = boardName; };

void TWeb::initWebServer() {
  Serial.print(F("WEB: Server initializing "));
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", String(), false,
                  TWeb::processingPlaceHolder(request));
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/style.css", "text/css");
  });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/script.js", "text/JavaScript");
  });

  server.onNotFound(notFound);
  AsyncElegantOTA.begin(&server);  // Запуск ElegantOTA для прошивки по OTA
  server.begin();                  // Запуск AsyncWebServer
  Serial.println(F("[OK]"));
}

void TWeb::notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String TWeb::processingPlaceHolder(AsyncWebServerRequest *request, const String &var) {
  if (var == "HEADERPLACEHOLDER") {
    String timeNow = getTimeString();
    char buffer[strlen(headerPlaceHolder) + boardName.length() +
                timeNow.length()];
    sprintf_P(buffer, headerPlaceHolder, boardName.c_str(),
              timeNow.c_str());
    return String(buffer);
  }
  if (var == "MAINPLACEHOLDER") {
    char buffer[strlen(mainPlaceHolder) + 10];
    sprintf_P(buffer, mainPlaceHolder, "NULL", "NULL");
    return String(buffer);
  }
  return "";
}

// Проверяем текущее состояние pin и возвращаем "checked" или пустую строку.
String TWeb::getPinStringStatus(uint8_t pin) {
  if (digitalRead(pin))
    return "checked";
  else
    return "";
}
