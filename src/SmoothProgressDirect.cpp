#include "SmoothProgressDirect.h"
#include "barstyle.h"

void SmoothProgressDirect::draw(uint8_t x, uint8_t y, uint8_t w, uint8_t pc) {
  uint16_t wPx = (w * 5) + (w - 1); // calculate the total w idth in px, including gaps
  uint16_t wFilled = ((uint32_t)wPx * 10UL * (uint32_t)pc) / 1000UL;
  uint16_t curFill = 0;
  uint8_t c[5] = {0}; // buffer for one character

  LCD.setCursor(x, y);


}
