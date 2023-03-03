#ifndef __STYLE_BATTSKINNY_H__
#define __STYLE_BATTSKINNY_H__

#include "style.h"

const style PROG_DECORATOR styleBattSkinny = {
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
      0b00111100
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
      0b00111100,
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
  .offsetLeft = 5,
  .offsetRight = 5
};

#endif