#ifndef __LIL_PROG_H__
#define __LIL_PROG_H__

#include "style.h"

#include <Arduino.h>

template <class T>
class LilProg {
public:
  LilProg(T& l, const style *s) : lcd(l), styles{s, NULL, NULL, NULL}, ns(1) {};
  LilProg(T& l, const style *s, const style *s1) : lcd(l), styles{s, s1, NULL, NULL}, ns(2) {};
  LilProg(T& l, const style *s, const style *s1, const style *s2) : lcd(l), styles{s, s1, s2, NULL}, ns(3) {};
  LilProg(T& l, const style *s, const style *s1, const style *s2, const style *s3) : lcd(l), styles{s, s1, s2, s3}, ns(4) {};
  void setStyle(uint8_t s);
  void setGeometry(uint8_t, uint8_t, uint8_t, uint8_t);
  void draw();
  void draw(uint8_t, uint8_t, uint8_t, uint8_t);

private:
  void initCharacters();
  void buildBlockChar(uint8_t, uint8_t, uint8_t);
  void buildCharacter(const mask *, uint8_t, uint8_t);

  T& lcd;
  const style *styles[4]; /* pointers to up to 4 styles */
  int8_t st = -1;         /* the current style in use */
  uint8_t ns;             /* the number of styles available */
  uint8_t pX, pY, width, transitionBlock, transitionBlockFill, filledBlocks;
  bool haveTransitionBlock;
  uint8_t count = 0;
};

#define AddrBlockLeft       0x04
#define AddrBlockRight      0x05
#define AddrBlockMidEmpty   0x06
#define AddrBlockMidFull    0x07

template <class T>
void LilProg<T>::initCharacters() {
  buildCharacter(&styles[st]->maskLeft,  5, AddrBlockLeft);
  buildCharacter(&styles[st]->maskRight, 0, AddrBlockRight);
  buildCharacter(&styles[st]->maskMid,   0, AddrBlockMidEmpty);
  buildCharacter(&styles[st]->maskMid,   5, AddrBlockMidFull);
}

/*
 * stored data:
 *
 * 0b00000000,
 * 0b00000000,
 * 0b00011000,
 * 0b00111100,
 * 0b00111100
 *
 * transpose to:
 *
 * 0b00000,
 * 0b00000,
 * 0b00011,
 * 0b00111,
 * 0b00111,
 * 0b00011,
 * 0b00000,
 * 0b00000
 */

template <class T>
void LilProg<T>::buildCharacter(const mask *m, uint8_t fill, uint8_t addr) {
  uint8_t c[8] = {0};
  uint8_t b;

  for (uint8_t col=0; col<5; col++) {
    if (fill > col) {
      b = 0xFF;
    } else {
      b = 0x00;
    }
    b &= m->neg[col];
    b |= m->pos[col];
    for (uint8_t row=0; row<8; row++) {
      c[row] |= ((b & 1) << (4 - col)); // transpose
      b >>= 1;
    }
  }

  lcd.createChar(addr, c);
}

template <class T>
void LilProg<T>::buildBlockChar(uint8_t block, uint8_t fill, uint8_t addr) {
    if (block == 0) {
      buildCharacter(&styles[st]->maskLeft, fill, addr);
    }
    else if (block == width - 1) {
      buildCharacter(&styles[st]->maskRight, fill, addr);
    }
    else {
      buildCharacter(&styles[st]->maskMid, fill, addr);
    }
}

template <class T>
void LilProg<T>::setGeometry(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
  if (pc > 100) {
    pc = 100;
  }
  // limit width due to use of uint8_t for width calculations
  if (w > 42) {
    w = 42;
  }
  width = w;
  pX = x;
  pY = y;

  /* calculate total width in px, including gaps, scale by percentage value */
  uint8_t wPx = (w*5) + (w-1) - styles[st]->offsetLeft - styles[st]->offsetRight;
  uint8_t wFilled = (uint8_t)(((uint32_t)wPx * 10UL * (uint32_t)pc) / 1000UL);
  uint8_t pFilled = wFilled + styles[st]->offsetLeft;

  transitionBlock = pFilled / 6;
  transitionBlockFill = pFilled % 6;
  haveTransitionBlock = (transitionBlockFill < 5);

  filledBlocks = transitionBlock;
  if (haveTransitionBlock && transitionBlock > 0) {
      filledBlocks = transitionBlock - 1;
  }
}

template <class T>
void LilProg<T>::setStyle(uint8_t s) {
  if (s >= ns) {
    return;
  }
  if (st != s) {
    st = s;
    initCharacters();
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
 *             fill: 012345
 * <-------------------w-------------------> =40
 * <> offsetLeft              offsetRight <>
 *   <----------------Wpx---------------->
 *   <----wFilled----><------wEmpty------>
 */
template <class T>
void LilProg<T>::draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
  if (st == -1) {
    setStyle(0);
  }
  setGeometry(x, y, w, pc);
  draw();
}

// TODO: optimise redraws
template <class T>
void LilProg<T>::draw() {
  if (haveTransitionBlock) {
    buildBlockChar(transitionBlock, transitionBlockFill, count);
  }

  // set entry point
  lcd.setCursor(pX, pY);

#ifdef LILPROG_DEBUG
  Serial.print("trb: ");
  Serial.println(transitionBlock);
  Serial.print("havetrb: ");
  Serial.println(haveTransitionBlock);
#endif

  // write characters
  uint8_t block = 0;
  do {
#ifdef LILPROG_DEBUG
    Serial.println(block);
#endif
    if (haveTransitionBlock && block == transitionBlock) {
      lcd.write(count);
    }
    else if (block == 0) {
      //lcd.print('L');
      lcd.write(AddrBlockLeft);
    }
    else if (block == width - 1) {
      //lcd.print('R');
      lcd.write(AddrBlockRight);
    }
    else if (block <= filledBlocks) {
      //lcd.print('F');
      lcd.write(AddrBlockMidFull);
    }
    else {
      //lcd.print('E');
      lcd.write(AddrBlockMidEmpty);
    }
  } while (block++ < width - 1);

#ifdef LILPROG_DEBUG
   Serial.println();
   Serial.print("filled: ");
   Serial.println(filledBlocks);
#endif

  // update address counter
  if (haveTransitionBlock) {
    count = (count + 1) % 4;
#ifdef LILPROG_DEBUG
    Serial.print("count updated to: ");
    Serial.println(count);
#endif
  }
}

#endif
