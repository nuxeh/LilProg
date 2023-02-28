#include "LilProg.h"

template <class T>
void LilProg<T>::buildCharacter(mask *n, mask *p, uint8_t fill, uint8_t addr) {
  uint8_t b;
  uint8_t c[8] = {0};

  for (uint8_t i=0; i<5; i++) {
    if (i <= fill) {
      b = 0xFF;
    } else {
      b = 0x00;
    }
    b &= n[i];
    b |= p[i];
    for (uint8_t j=0; j<8; j++) {
      c[j] |= (b[j] & (1 << j)); // transpose
    }
  }

  LCD.createChar(addr, c);
}

template <class T>
void LilProg<T>::printChar(uint8_t w, uint8_t n, uint8_t fill) {
  if (n == 0) {
    buildCharacter(st.maskLN, st.maskLP, fill, 0);
    LCD.print("\10");
  } else if (n == w) {
    buildCharacter(st.maskRN, st.maskRP, fill, 0);
    LCD.print("\10");
  } else {
    buildCharacter(st.maskMN, st.maskMP, fill, 0);
    LCD.print("\10");
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

  uint8_t wPx = (w * 5) + (w - 1); // total width in px, including gaps
  wPx -= st->offsetL + st->offsetR; // reduce by edge offsets

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

  LCD.setCursor(x, y);

  for (uint8_t i=0; i<w; i++) {
    if (i <= filledBlocks) {
      printChar(w, i, 4);
    } else if (i == filledBlocks + 1 && haveTransitionBlock) {
      printChar(w, i, transitionBlockFill);
    } else {
      printChar(w, i, 0);
    }
  }
}