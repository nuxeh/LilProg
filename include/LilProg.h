#ifndef __LIL_PROG_H__
#define __LIL_PROG_H__

#include "style.h"

#include <Arduino.h>

template <class T>
class LilProg {
public:
  LilProg(T& l, const style& s);
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

#define AddrBlockTransition 0x00
#define AddrBlockLeft       0x01
#define AddrBlockRight      0x02
#define AddrBlockMidEmpty   0x03
#define AddrBlockMidFull    0x04

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
LilProg<T>::LilProg(T& l, const style& s) : lcd(l), st(s) {
  initCharacters();
}

template <class T>
void LilProg<T>::initCharacters() {

}

template <class T>
void LilProg<T>::buildCharacter(const mask *m, uint8_t fill, uint8_t addr) {
  uint8_t b;
  uint8_t c[8] = {0};

  for (uint8_t i=1; i<6; i++) {
    if (i <= fill) {
      b = 0xFF;
    } else {
      b = 0x00;
    }
    b &= m->neg[i-1];
    //b |= *p[i];
    for (uint8_t j=0; j<8; j++) {
      c[j] |= ((b & 1) << (5 - i)); // transpose
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

  if (transitionBlockFill < 5) {
    haveTransitionBlock = true;
    if (transitionBlock > 0) {
      filledBlocks = transitionBlock - 1;
    }
  } else {
    haveTransitionBlock = false;
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
  //lcd.write(AddrBlockLeft);

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
      lcd.print('L');
    }
    else if (block == width - 1) {
      lcd.print('R');
    }
    else if (block <= filledBlocks) {
      lcd.print('F');
    }
    else {
      lcd.print('E');
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
