#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LilProgTextMode.h>

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
LilProgTextMode<LiquidCrystal_I2C> prog(lcd);

void setup() {
  Serial.begin(115200);
  #define VCC_LCD_EN 2
  #define VCC_RUN_EN A3
  pinMode(VCC_RUN_EN, OUTPUT);
  pinMode(VCC_LCD_EN, OUTPUT);
  digitalWrite(VCC_RUN_EN, LOW);
  digitalWrite(VCC_LCD_EN, LOW);
  Wire.begin();
  lcd.begin();
}

uint8_t pc = 0;

void loop() {
  uint32_t t1 = micros();
  prog.draw(0, 0, 16, pc);
  Serial.println(micros() - t1);
  pc = (pc + 1) % 100;
  delay(100);
}
