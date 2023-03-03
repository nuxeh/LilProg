#ifndef __STYLE_SKINNYBLOCKY_H__
#define __STYLE_SKINNYBLOCKY_H__

#include "style.h"

const style PROG_DECORATOR styleSkinnyBlocky = {
  .maskLeft = {
    .neg = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00011000,
      0b00011000
    },
    .pos = {
      0b00000000,
      0b00111100,
      0b01000010,
      0b01000010,
      0b01000010
    },
  },
  .maskRight = {
    .neg = {
      0b00011000,
      0b00011000,
      0b00000000,
      0b00000000,
      0b00000000
    },
    .pos = {
      0b01000010,
      0b01000010,
      0b01000010,
      0b00111100,
      0b00000000
    },
  },
  .maskMid = {
    .neg = {
      0b00011000,
      0b00011000,
      0b00000000,
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
  .offsetLeft = 3,
  .offsetRight = 3
};

#endif