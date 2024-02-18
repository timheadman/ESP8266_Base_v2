#include "TNtc.h"

#define BETA 3950
#define NOMINAL 25  // номинальная температура в градусах Цельсия
#define RESISTOR 10000
#define THERMISTOR 10000

float TNtc::getTemperature() {
  float a0Value = (float)analogRead(pin);
  float R = -10 * a0Value / (a0Value - 1024);
  uint16_t i = 0;
  while (ADDR[i][1] > R) {
    i++;
  }
  float result = (R - ADDR[i][1]) * (ADDR[i - 1][0] - ADDR[i][0]) /
                     (ADDR[i - 1][1] - ADDR[i][1]) +
                 ADDR[i][0];
  return result;
}

float TNtc::getTemperatureB() {
  float a0Value = (float)analogRead(pin);
  float R = RESISTOR / (1023.0f / a0Value - 1.0);
  float kSteinhart =
      (log(R / (float)THERMISTOR) / BETA) + 1.0f / (NOMINAL + 273.15f);
  return (1.0f / kSteinhart - 273.15);
}