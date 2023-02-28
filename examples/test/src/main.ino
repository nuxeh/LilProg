#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LilProg.h>
#include <styleRounded.h>

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
LilProg<LiquidCrystal_I2C> progress(lcd, rounded);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.begin();
}

uint8_t pc = 0;

void loop() {
  uint32_t t1 = micros();
  //progress.draw(0, 0, 16, pc);
  Serial.print(micros() - t1);
  pc = (pc + 1) % 100;
  delay(100);
}
