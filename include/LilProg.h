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

#define AddrBlockTransition 0x08
#define AddrBlockLeft       0x09
#define AddrBlockRight      0x0A
#define AddrBlockMidEmpty   0x0B
#define AddrBlockMidFull    0x0C

/*
  0b00000000,
  0b00000000,
  0b00011000,
  0b00111100,
  0b00111100

  0b00000,
  0b00000,
  0b00011,
  0b00111,
  0b00111,
  0b00011,
  0b00000,
  0b00000
 */

template <class T>
void LilProg<T>::buildCharacter(const mask *n, const mask *p, uint8_t fill, uint8_t addr) {
  uint8_t b;
  uint8_t c[8] = {0};

  for (uint8_t i=1; i<6; i++) {
    if (i <= fill) {
      b = 0xFF;
    } else {
      b = 0x00;
    }
    //b &= *n[i];
    //b |= *p[i];
    for (uint8_t j=0; j<8; j++) {
      c[j] |= ((b & 1) << (5 - i)); // transpose
      b >>= 1;
    }
  }

  lcd.createChar(addr, c);
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
 *             fill: 012345
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
  uint8_t transitionBlockFill = pFilled % 6;

  uint8_t filledBlocks;
  bool haveTransitionBlock;

  if (transitionBlockFill < 5) {
    haveTransitionBlock = true;
    filledBlocks = transitionBlock - 1;
  } else {
    haveTransitionBlock = false;
    filledBlocks = transitionBlock;
  }

  /* make left block */
  if (transitionBlock == 0) {
    buildCharacter(&st.maskLN, &st.maskLP, transitionBlockFill + 1, AddrBlockLeft);
  } else {
    buildCharacter(&st.maskLN, &st.maskLP, 5, AddrBlockLeft);
  }

  /* make right block */
  if (transitionBlock == w - 1) {
    buildCharacter(&st.maskRN, &st.maskRP, transitionBlockFill + 1, AddrBlockRight);
  } else {
    buildCharacter(&st.maskRN, &st.maskRP, 5, AddrBlockRight);
  }

  lcd.setCursor(x, y);
  lcd.write(AddrBlockLeft);

  uint8_t block;
  for (block=0; block<filledBlocks; block++) {

  }
  if (haveTransitionBlock) {

    block++;
  }
  for (; block<width; block++) {

  }

  lcd.write(AddrBlockRight);
}




/*
 *
 *
 *
 *
 *
 *
 *
 */



#endif
