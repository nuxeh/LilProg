#ifndef __LIL_PROG_H__
#define __LIL_PROG_H__

#include "style.h"

#include <Arduino.h>

template <class T>
class LilProg {
public:
  LilProg(T& l, const style& s) : lcd(l), st(s) {};
  void begin();
  void setGeometry(uint8_t, uint8_t, uint8_t, uint8_t);
  void draw();
  void draw(uint8_t, uint8_t, uint8_t, uint8_t);

private:
  void initCharacters();
  void buildCharacter(const mask *, uint8_t, uint8_t);
  void printChar(uint8_t, uint8_t);

  T& lcd;
  const style& st;
  uint8_t pX, pY, width, transitionBlock, transitionBlockFill, filledBlocks;
  bool haveTransitionBlock;
  uint8_t count = 0;
};

#define AddrBlockLeft       0x05
#define AddrBlockRight      0x06
#define AddrBlockMidEmpty   0x07
#define AddrBlockMidFull    0x08

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
void LilProg<T>::begin() {
  initCharacters();
}

template <class T>
void LilProg<T>::initCharacters() {
  buildCharacter(&st.maskLeft,  5, AddrBlockLeft);
  buildCharacter(&st.maskRight, 0, AddrBlockRight);
  buildCharacter(&st.maskMid,   0, AddrBlockMidEmpty);
  buildCharacter(&st.maskMid,   5, AddrBlockMidFull);
}

template <class T>
void LilProg<T>::buildCharacter(const mask *m, uint8_t fill, uint8_t addr) {
  uint8_t b;
  uint8_t c[8] = {0};

  for (uint8_t col=0; col<5; col++) {
    if (fill > col) {
      b = 0xFF;
    } else {
      b = 0x00;
    }
    //b &= m->neg[i-1];
    //b |= m->pos[i-1];
    for (uint8_t row=0; row<8; row++) {
      c[row] |= ((b & 1) << (4 - col)); // transpose
      b >>= 1;
    }
  }

  lcd.createChar(addr, c);
}

template <class T>
void LilProg<T>::setGeometry(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
  if (pc > 100) {
    pc = 100;
  }
  if (w > 42) {
    w = 42;
  }
  width = w;
  pX = x;
  pY = y;

  uint8_t wPx = (w * 5) + (w - 1) - st.offsetLeft - st.offsetRight; // total width in px, including gaps
  uint8_t wFilled = (uint8_t)(((uint32_t)wPx * 10UL * (uint32_t)pc) / 1000UL); // scale by percentage
  uint8_t pFilled = wFilled + st.offsetLeft;

  transitionBlock = pFilled / 6;
  transitionBlockFill = pFilled % 6;
  haveTransitionBlock = (transitionBlockFill < 5);

  if (haveTransitionBlock) {
    if (transitionBlock > 0) {
      filledBlocks = transitionBlock - 1;
    }
  } else {
    filledBlocks = transitionBlock;
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
  setGeometry(x, y, w, pc);
  draw();

#if 0
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

  /* make filled and empty mid blocks */
  buildCharacter(&st.maskMN, &st.maskMP, 0, AddrBlockMidEmpty);
  buildCharacter(&st.maskMN, &st.maskMP, 5, AddrBlockMidFull);

  /* make transition block */
  if (haveTransitionBlock) {
    buildCharacter(&st.maskMN, &st.maskMP, transitionBlockFill + 1, AddrBlockTransition);
  }
#endif
}

template <class T>
void LilProg<T>::draw() {
  if (haveTransitionBlock) {
    // make the transition character
    count = (count + 1) % 4;
#ifdef LILPROG_DEBUG
    Serial.print("count updated to: ");
    Serial.println(count);
#endif
  }

  lcd.setCursor(pX, pY);

#ifdef LILPROG_DEBUG
  Serial.print("trb: ");
  Serial.println(transitionBlock);
  Serial.print("havetrb: ");
  Serial.println(haveTransitionBlock);
#endif

  uint8_t block = 0;
  do {
#ifdef LILPROG_DEBUG
    Serial.println(block);
#endif
    if (haveTransitionBlock && block == transitionBlock) {
      lcd.print('T');
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
