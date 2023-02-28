#ifndef __LIL_PROG_H__
#define __LIL_PROG_H__

#include "style.h"

#include <Arduino.h>

template <class T>
class LilProg {
public:
  LilProg(T& l, const style& s) : lcd(l), st(s) {}
  void draw(uint8_t, uint8_t, uint8_t, uint8_t);

private:
  void buildCharacter(const mask *, const mask *, uint8_t, uint8_t);
  void printChar(uint8_t, uint8_t);

  T& lcd;
  const style& st;
  uint8_t pX, pY, width;
};

template <class T>
void LilProg<T>::buildCharacter(const mask *n, const mask *p, uint8_t fill, uint8_t addr) {
  uint8_t b;
  uint8_t c[8] = {0};

  for (uint8_t i=0; i<5; i++) {
    if (i <= fill) {
      b = 0xFF;
    } else {
      b = 0x00;
    }
    Serial.println(b, BIN);
    b &= *n[i];
    Serial.println(b, BIN);
    b |= *p[i];
    Serial.println(b, BIN);
    for (uint8_t j=0; j<8; j++) {
      c[j] |= (b & (1 << j)); // transpose
    }
  }

  lcd.createChar(addr, c);
}

template <class T>
void LilProg<T>::printChar(uint8_t n, uint8_t fill) {
  if (n == 0) {
    buildCharacter(&st.maskLN, &st.maskLP, fill, 0);
    lcd.setCursor(pX + n, pY);
    lcd.print("\10");
  } else if (n == width) {
    buildCharacter(&st.maskRN, &st.maskRP, fill, 0);
    lcd.setCursor(pX + n, pY);
    lcd.print("\10");
  } else {
    buildCharacter(&st.maskMN, &st.maskMP, fill, 0);
    lcd.setCursor(pX + n, pY);
    lcd.print("\10");
  }
}

/*
 *           1111111111222222222233333333334
 * 01234567890123456789012345678901234567890
 * ..... ..... ..... ..... ..... ..... .....
 * ..... ..... ..... ..... ..... ..... .....
 * .###. ..... .###. ..... .###. ..... .###.
 * #...# ..... #...# ..... #...# ..... #...#
 * ##### ..... ##### ..... ##### ..... #####
 * #.... ..... #.... ..... #.... ..... #....
 * .###. ..... .###. ..... .###. ..... .###.
 * ..... ..... ..... ..... ..... ..... .....
 * <-------------------w-------------------> =40
 * <> offsetL                     offsetR <>
 *   <----------------Wpx---------------->
 *   <----wFilled----><------wEmpty------>
 */
template <class T>
void LilProg<T>::draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
  if (w > 42) {
    w = 42;
  }
  if (pc > 100) {
    pc = 100;
  }

  pX = x;
  pY = y;
  width = w;

  uint8_t wPx = (w * 5) + (w - 1); // total width in px, including gaps
  wPx -= st.offsetL + st.offsetR; // reduce by edge offsets

  uint8_t wFilled = (uint8_t)(((uint32_t)wPx * 10UL * (uint32_t)pc) / 1000UL); // scale by percentage
  uint8_t pFilled = wFilled + st.offsetL;

  uint8_t transitionBlock = pFilled / 6;
  uint8_t filledBlocks = transitionBlock;
  uint8_t transitionBlockFill = pFilled % 6;
  bool haveTransitionBlock = (transitionBlockFill < 5);

  // last pixel is in the gap
  if (haveTransitionBlock) {
    filledBlocks -= 1;
  }

  for (uint8_t i=0; i<w; i++) {
    if (i <= filledBlocks) {
      printChar(i, 4);
    } else if (i == filledBlocks + 1 && haveTransitionBlock) {
      printChar(i, transitionBlockFill);
    } else {
      printChar(i, 0);
    }
  }
}

#endif
