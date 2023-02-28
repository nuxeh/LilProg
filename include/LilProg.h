#ifndef __LIL_PROG_H__
#define __LIL_PROG_H__

#include "style.h"

#include <Arduino.h>

template <class T>
class LilProg {
public:
  LilProg(T& l, const style& s) : lcd(l), st(s) {}
  void draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc);
  const style& st;
  T& lcd;
private:
  void buildCharacter(mask *p, mask *n, uint8_t fill, uint8_t addr);
  void printChar(uint8_t w, uint8_t n, uint8_t fill);
};

#endif
