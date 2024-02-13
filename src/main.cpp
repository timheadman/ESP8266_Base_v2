#include "main.h"

// ***** ADS1115 ***** //
// Адрес микросхемы
// 0x48 - ADDR pin connected to GROUND (default)
// 0x49 - ADDR pin connected to VDD
// 0x4A - ADDR pin connected to SDA
// 0x4B - ADDR pin connected to SCL
//
// Настройка входного делителя, в зависимости от максимального входного
// напряжения
//                                  Vin MAX         ADS1115
// GAIN_TWOTHIRDS  // 2/3x gain +/- 6.144V  1 bit = 0.1875 mV (default)
// GAIN_ONE        // 1x gain   +/- 4.096V  1 bit = 0.125 mV
// GAIN_TWO        // 2x gain   +/- 2.048V  1 bit = 0.0625 mV
// GAIN_FOUR       // 4x gain   +/- 1.024V  1 bit = 0.03125 mV
// GAIN_EIGHT      // 8x gain   +/- 0.512V  1 bit = 0.015625 mV
// GAIN_SIXTEEN    // 16x gain  +/- 0.256V  1 bit = 0.0078125 mV
#define ADS1115_GAIN GAIN_TWOTHIRDS
Adafruit_ADS1115 ads;
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                        MAIN                        */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void setup(void) {
  Serial.begin(115200);
  initLCD();
  initADS1115();
}

void loop(void) {
  printADS1115();

  delay(2500);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                     FUNCTIONS                      */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void initLCD() {
  lcd.init();
  lcd.backlight();
}

void initADS1115() {
  Serial.print("\nInitializing ADS1115 - ");
  if (!ads.begin(0x48)) {
    Serial.print("Failed to initialize ADS. Please restart.");
    while (1)
      ;
  }
  ads.setGain(ADS1115_GAIN);
  Serial.println("OK");
}

void printADS1115() {
  int16_t raw; 
  raw = ads.readADC_SingleEnded(0);
  int16_t adc0 = raw <= 0 ? 0 : raw;
  float voltsA0 = ads.computeVolts(adc0);

  raw = ads.readADC_SingleEnded(1);
  int16_t adc1 = raw <= 0 ? 0 : raw;
  float voltsA1 = ads.computeVolts(adc1);

  raw = ads.readADC_SingleEnded(2);
  int16_t adc2 = raw <= 0 ? 0 : raw;
  float voltsA2 = ads.computeVolts(adc2);

  raw = ads.readADC_SingleEnded(3);
  int16_t adc3 = raw <= 0 ? 0 : raw;
  float voltsA3 = ads.computeVolts(adc3);

  Serial.print("A0:\t" + String(adc0) + "\t" + String(voltsA0, 4) + "\n");
  Serial.print("A1:\t" + String(adc1) + "\t" + String(voltsA1, 4) + "\n");
  Serial.print("A2:\t" + String(adc2) + "\t" + String(voltsA2, 4) + "\n");
  Serial.print("A3:\t" + String(adc3) + "\t" + String(voltsA3, 4) + "\n\n");

  lcd.setCursor(0, 0);
  lcd.print(String(voltsA0, 4) + " " + String(voltsA1, 4));
  lcd.setCursor(0, 1);
  lcd.print(String(voltsA2, 4) + " " + String(voltsA3, 4));
}
