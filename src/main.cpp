#include "main.h"
// AP IP address: 192.168.4.1, set manual IP in network settings
GTimer timerOneSecond(MS);
struct tm timeStructureNow;

void setup() {
  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.setTimeout(60);
  wifiManager.autoConnect();

  configTime("MSK-3", 0, "pool.ntp.org");
  timerOneSecond.setInterval(1000);
}

void loop() {
  if (timerOneSecond.isReady()) triggerOneSecond();
}

void triggerOneSecond() {
  updateTime();
  if (time(nullptr) > 1700000000)
    Serial.printf("%lld (%d:%d:%d)\n", time(nullptr), timeStructureNow.tm_hour,
                  timeStructureNow.tm_min, timeStructureNow.tm_sec);
  else
    Serial.printf("NTR synchronization failed\n");
}

void updateTime() {
  time_t unixTimeNow;
  time(&unixTimeNow);
  localtime_r(&unixTimeNow, &timeStructureNow);
}
