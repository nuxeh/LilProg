#ifndef __STYLE_SKINNY_H__
#define __STYLE_SKINNY_H__

#include "style.h"

const style PROG_DECORATOR styleSkinny = {
  .maskLeft = {
    .neg = {
      0b00000000,
      0b00000000,
      0b00011000,
      0b00011000,
      0b00011000
    },
    .pos = {
      0b00111100,
      0b01000010,
      0b01000010,
      0b01000010,
      0b01000010
    },
  },
  .maskRight = {
    .neg = {
      0b00011000,
      0b00011000,
      0b00011000,
      0b00000000,
      0b00000000
    },
    .pos = {
      0b01000010,
      0b01000010,
      0b01000010,
      0b01000010,
      0b00111100
    },
  },
  .maskMid = {
    .neg = {
      0b00011000,
      0b00011000,
      0b00011000,
      0b00011000,
      0b00011000
    },
    .pos = {
      0b01000010,
      0b01000010,
      0b01000010,
      0b01000010,
      0b01000010
    },
  },
  .offsetLeft = 2,
  .offsetRight = 2
};

#endif