#ifndef __STYLE_ROUNDED_H__
#define __STYLE_ROUNDED_H__

#include "style.h"

const style PROG_DECORATOR rounded = {
  .maskLeft = {
    .neg = {
      0b00000000,
      0b00000000,
      0b00011000,
      0b00111100,
      0b00111100
    },
    .pos = {
      0b00111100,
      0b01000010,
      0b10000001,
      0b10000001,
      0b10000001
    },
  },
  .maskRight = {
    .neg = {
      0b00111100,
      0b00111100,
      0b00011000,
      0b00000000,
      0b00000000
    },
    .pos = {
      0b10000001,
      0b10000001,
      0b10000001,
      0b01000010,
      0b00111100
    },
  },
  .maskMid = {
    .neg = {
      0b00111100,
      0b00111100,
      0b00111100,
      0b00111100,
      0b00111100
    },
    .pos = {
      0b10000001,
      0b10000001,
      0b10000001,
      0b10000001,
      0b10000001
    },
  },
  .offsetLeft = 2,
  .offsetRight = 2
};

#endif