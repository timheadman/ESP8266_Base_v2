#include "main.h"
// AP IP address: 192.168.4.1, set manual IP in network settings

void configModeCallback(WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  // if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.setTimeout(60);
  // set callback that gets called when connecting to previous WiFi fails, and
  // enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect();
  
}

void loop() {
  // put your main code here, to run repeatedly:
}