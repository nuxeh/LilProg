#ifndef __PROGRESS_H__

#include "style.h"

#include <Arduino.h>

template <class T>
class LilProg {
  LilProg(LCD& l, style& s) : lcd(l), st(s) {}
  void draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc);

private:
  void buildCharacter(mask *p, mask *n, uint8_t fill, uint8_t addr);
  void printChar(uint8_t w, uint8_t n, uint8_t fill) {

  style& st;
  T& lcd;
};

#endif