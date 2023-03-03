/*
 * Draw progress bars with multiple styles
 *
 * Note that bars with differing styles cannot be drawn at the same time, since
 * custom characters must share 8 addresses in display RAM, and must remain in
 * RAM to be displayed as the display refreshes.
 *
 * For similar reasons, a maximum of 4 progress bars can be reliably displayed
 * at one time, due to the fact that each bar will (potentially) require a
 * "transition" character with partial fill.
 *
 * Currently a LilProg object may be initialised with up to 4 styles.
 */

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LilProg.h>
#include <styleSquare.h>
#include <styleSkinnyBlocky.h>

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
LilProg<LiquidCrystal_I2C> prog(lcd, &styleSquare, &styleSkinnyBlocky);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.begin();
}

uint8_t pc = 0;

void loop() {
  for (uint8_t i=0; i<=100; i++) {
    prog.setStyle(0);
    prog.draw(0, 0, 16, i);
    delay(100);
  }

  delay(1000);

  for (uint8_t i=0; i<=100; i++) {
    prog.setStyle(1);
    prog.draw(0, 0, 16, i);
    delay(100);
  }

  delay(1000);
}
