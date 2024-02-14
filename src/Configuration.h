#ifndef ESP8266_BASE_V2_CONFIG_H_
#define ESP8266_BASE_V2_CONFIG_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

class Configuration {
 private:
  String fileName;
  String boardName;
  String host;
  uint16_t port;
  String botToken;
  int64_t adminChatId;
  String dbIp;
  uint16_t dbPort;
  String dbUser;
  String dbPwd;
  String dbName;

 public:
  Configuration() { fileName = "/config.json"; }

  String getFileName() { return fileName; }
  String getBoardName() { return boardName; }
  String getHost() { return host; }
  uint16_t getPort() { return port; }
  String getBotToken() { return botToken; }
  int64_t getAdminChatId() { return adminChatId; }
  String getDbIp() { return dbIp; }
  uint16_t getDbPort() { return dbPort; }
  String getDbUser() { return dbUser; }
  String getDbPwd() { return dbPwd; }
  String getDbName() { return dbName; }

  bool loadConfiguration();
  void saveConfiguration();
  void printConfiguration();
};

#endif  // ESP8266_BASE_V2_CONFIG_H_