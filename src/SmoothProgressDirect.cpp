#include "SmoothProgressDirect.h"
#include "barstyle.h"

void buildCharacter() {

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

void SmoothProgressDirect::draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
  if (w > 42) {
    w = 42;
  }
  if (pc > 100) {
    pc = 100;
  }

  uint8_t wPx = (w * 5) + (w - 1); // calculate the total w idth in px, including gaps
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

  uint8_t emptyBlocks = w - filledBlocks - 2;

  uint16_t curFill = 0;
  uint8_t c[5] = {0}; // buffer for one character

  LCD.setCursor(x, y);


}
