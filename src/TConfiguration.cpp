#include "TConfiguration.h"

TConfiguration::TConfiguration()
    : fileName("/config.json"),
      boardName(""),
      host(""),
      port(0),
      botToken(""),
      adminChatId(0),
      dbIp(""),
      dbPort(0),
      dbUser(""),
      dbPwd(""),
      dbName("") {}

/**
 * Загрузка конфигурационного файла из LittleFS
 * @return true или false
 */
bool TConfiguration::loadConfiguration() {
  // Открываем файл для чтения
  Serial.println(F("*CFG: Loading configuration..."));
  File configFile = LittleFS.open(fileName, "r");
  if (!configFile) {
    Serial.println(F("*CFG: Failed to open config file"));
    return false;
  }

  // Документация Arduino JSON: https://arduinojson.org/v6/
  // Расчет необходимой памяти под JSON массив
  // https://arduinojson.org/v6/assistant/
  DynamicJsonDocument jsonDoc(512);
  DeserializationError error = deserializeJson(jsonDoc, configFile);
  if (error) {
    Serial.print(F("*CFG: deserializeJson() failed: "));
    Serial.println(error.f_str());
    return false;
  }
  // Визуализация распознанного JSON (для отладки)
  Serial.print(F("*CFG: Loading from file "));
  // serializeJsonPretty(jsonDoc, Serial);
  boardName = jsonDoc["boardName"].as<String>();
  // Telegram
  botToken = jsonDoc["botToken"].as<String>();
  adminChatId = jsonDoc["adminChatId"].as<int64_t>();
  // Database
  host = jsonDoc["host"].as<String>();
  port = jsonDoc["port"].as<uint16_t>();
  dbIp = jsonDoc["dbIp"].as<String>();
  dbPort = jsonDoc["dbPort"].as<uint16_t>();
  dbUser = jsonDoc["dbUser"].as<String>();
  dbPwd = jsonDoc["dbPwd"].as<String>();
  dbName = jsonDoc["dbName"].as<String>();

  Serial.println();

  configFile.close();
  return true;
}

/**
 * Загрузка конфигурационного файла в LittleFS
 */
void TConfiguration::saveConfiguration() {
  // Open file for writing
  File configFile = LittleFS.open(fileName, "w+");
  if (!configFile) {
    Serial.println(F("*CFG: Failed to create file"));
    return;
  }

  // Документация Arduino JSON: https://arduinojson.org/v6/
  // Расчет необходимой памяти под JSON массив
  // https://arduinojson.org/v6/assistant/
  DynamicJsonDocument jsonDoc(512);
  jsonDoc["boardName"] = boardName;
  // Telegram
  jsonDoc["botToken"] = botToken;
  jsonDoc["adminChatId"] = adminChatId;
  // Database
  jsonDoc["host"] = host;
  jsonDoc["port"] = port;
  jsonDoc["sqlIP"] = dbIp;
  jsonDoc["sqlPort"] = dbPort;
  jsonDoc["sqlUser"] = dbUser;
  jsonDoc["sqlPwd"] = dbPwd;
  jsonDoc["sqlDb"] = dbName;

  // Serialize JSON to file
  if (serializeJson(jsonDoc, configFile) == 0) {
    Serial.println(F("*CFG: Failed to write to file"));
  }
  // Close the file (File's destructor doesn't close the file)
  configFile.close();
}

/**
 * Вывести содержимое конфигурационного файла в Serial порт.
 */
void TConfiguration::printConfiguration() {
  // Open file for reading
  File file = LittleFS.open(fileName, "r");
  if (!file) {
    Serial.print(F("*CFG: Failed to read file config file"));
    return;
  }
  Serial.print("*CFG: ");

  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  file.close();
}
