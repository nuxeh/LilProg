#ifndef __LIL_PROG_H__
#define __LIL_PROG_H__

#include "style.h"

#include <Arduino.h>

template <class T>
class LilProgSmoothBar {
public:
  LilProgSmoothBar(T& l) : lcd(l) {};
  LilProgSmoothBar(T& l, uint8_t colMask) : lcd(l), colMask(colMask) {};
  void begin();
  void setGeometry(uint8_t, uint8_t, uint8_t, uint8_t);
  void draw();
  void draw(uint8_t, uint8_t, uint8_t, uint8_t);

private:
  void initCharacters();
  void buildBlockChar(uint8_t, uint8_t, uint8_t);
  void buildCharacter(uint8_t, uint8_t);

  T& lcd;
  uint8_t pX, pY, width, transitionBlock, transitionBlockFill, filledBlocks;
  bool haveTransitionBlock;
  uint8_t colMask = 0xFF;
  uint8_t count = 0;
};

#define AddrBlockLeft       0x04
#define AddrBlockRight      0x05
#define AddrBlockMidEmpty   0x06
#define AddrBlockMidFull    0x07

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
void LilProgSmoothBar<T>::begin() {
  initCharacters();
}

template <class T>
void LilProgSmoothBar<T>::initCharacters() {
  buildCharacter(5, AddrBlockLeft);
  buildCharacter(0, AddrBlockRight);
  buildCharacter(0, AddrBlockMidEmpty);
  buildCharacter(5, AddrBlockMidFull);
}

template <class T>
void LilProgSmoothBar<T>::buildCharacter(uint8_t fill, uint8_t addr) {
  uint8_t c[8] = {0};
  uint8_t b;

  for (uint8_t col=0; col<5; col++) {
    if (fill > col) {
      b = colMask;
    } else {
      b = 0x00;
    }
    for (uint8_t row=0; row<8; row++) {
      c[row] |= ((b & 1) << (4 - col)); // transpose
      b >>= 1;
    }
  }

  lcd.createChar(addr, c);
}

template <class T>
void LilProgSmoothBar<T>::setGeometry(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
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

  uint8_t wPx = (w * 5) + (w - 1); // total width in px, including gaps
  uint8_t pFilled = (uint8_t)(((uint32_t)wPx * 10UL * (uint32_t)pc) / 1000UL); // scale by percentage

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
void LilProgSmoothBar<T>::draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
  setGeometry(x, y, w, pc);
  draw();
}

// TODO: optimise redraws
template <class T>
void LilProgSmoothBar<T>::draw() {
  if (haveTransitionBlock) {
    buildCharacter(transitionBlockFill, count);
  }

#ifdef LILPROG_DEBUG
  Serial.print("trb: ");
  Serial.println(transitionBlock);
  Serial.print("havetrb: ");
  Serial.println(haveTransitionBlock);
#endif

  // write characters
  Serial.println();
  uint8_t block = 0;
  do {
    // set entry point
    lcd.setCursor(pX + block, pY);

#ifdef LILPROG_DEBUG
    //Serial.print(block);
#endif
    if (haveTransitionBlock && block == transitionBlock) {
      lcd.write(count);
      Serial.print("T");
    }
    else if (block == 0) {
      lcd.write(AddrBlockLeft);
      Serial.print("L");
    }
    else if (block == width - 1) {
      lcd.write(AddrBlockRight);
      Serial.print("R");
    }
    else if (block <= filledBlocks) {
      lcd.write(AddrBlockMidFull);
      Serial.print("F");
    }
    else {
      lcd.write(AddrBlockMidEmpty);
      Serial.print("E");
    }
  } while (block++ < width - 1);

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
