#ifndef __STYLE_BATTSKINNYBLOCKY_H__
#define __STYLE_BATTSKINNYBLOCKY_H__

#include "style.h"

const style PROG_DECORATOR styleBattSkinnyBlocky = {
  .maskLeft = {
    .neg = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000
    },
    .pos = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b01111110
    },
  },
  .maskRight = {
    .neg = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000
    },
    .pos = {
      0b01111110,
      0b00011000,
      0b00011000,
      0b00000000,
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
  .offsetLeft = 5,
  .offsetRight = 5
};

#endif