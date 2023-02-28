#include <Arduino.h>
#include <LiquidSerial_I2C>
#include <LilProg.h>
#include <styleRounded.h>

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
LilProg progress(lcd, rounded);

void setup() {
  Serial.begin(115200);
  lcd.begin();
}

uint8_t pc = 0;

void loop() {
  uint32_t t1 = micros();
  progress.draw(0, 0, 16, pc);
  Serial.print(micros() - t1);
  pc = (pc + 1) % 100;
  delay(100);
}
