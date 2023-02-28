#ifndef __PROGRESS_H__

#include "style.h"

#include <Arduino.h>

#if defined(LiquidCrystal_I2C_h) 
#define LCD LiquidCrystal_I2C
//#if defined(hd44780_h) 
#elif defined(hd44780_I2Cexp_h)
#define LCD hd44780_I2Cexp
#elif defined(hd44780_HC1627_I2C_h)
#define LCD hd44780_HC1627_I2C
#elif defined(hd44780_I2Clcd_h)
#define LCD hd44780_I2Clcd 
#elif defined(FDB_LIQUID_CRYSTAL_I2C_H)
#define LCD LiquidCrystal_I2C
#elif defined(LiquidCrystal_h)
#define LCD LiquidCrystal
#else
#error "No supported LiquidCrystal library included. Please check that the LiquidCrystal library is included"
#endif

class LilProg {
  LilProg(LCD& l, style& s) : lcd(l), st(s) {}
  void draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc);

private:
  void buildCharacter(mask *p, mask *n, uint8_t fill, uint8_t n);
  void printChar(uint8_t w, uint8_t n, uint8_t fill) {

  style& st;
  LCD& lcd;
};

#endif
