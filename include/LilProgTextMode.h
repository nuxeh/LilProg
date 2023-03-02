#ifndef __LIL_PROG_TEXT_MODE_H__
#define __LIL_PROG_TEXT_MODE_H__

#include <Arduino.h>

#define LEFT       0
#define RIGHT      1
#define TRANSITION 2
#define EMPTY      3
#define FULL       4

typedef struct {
  char l;
  char r;
  char t;
  char e;
  char f;
} glyphs;

typedef union {
  char l[5];
  glyphs g;
} glyphArray;

template <class T>
class LilProgTextMode {
public:
  LilProgTextMode(T& lcd, char l, char r, char t, char e, char f) : lcd(lcd), g({l, r, t, e, f}) {};
  void setGeometry(uint8_t, uint8_t, uint8_t, uint8_t);
  void draw();
  void draw(uint8_t, uint8_t, uint8_t, uint8_t);

private:
  T& lcd;
  char g[5];
  uint8_t pX, pY, width, transitionBlock, transitionBlockFill, filledBlocks;
  bool haveTransitionBlock;
};

template <class T>
void LilProgTextMode<T>::setGeometry(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
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
void LilProgTextMode<T>::draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
  setGeometry(x, y, w, pc);
  draw();
}

// TODO: optimise redraws
template <class T>
void LilProgTextMode<T>::draw() {
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
      lcd.print(g[TRANSITION]);
    }
    else if (block == 0) {
      lcd.print(g[LEFT]);
    }
    else if (block == width - 1) {
      lcd.print(g[RIGHT]);
    }
    else if (block <= filledBlocks) {
      lcd.print(g[FULL]);
    }
    else {
      lcd.print(g[EMPTY]);
    }
  } while (block++ < width - 1);
}

#endif
