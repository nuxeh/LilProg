#ifndef __STYLE_SQUARE_H__
#define __STYLE_SQUARE_H__

#include "style.h"

const style PROG_DECORATOR square = {
  .maskLeft = {
    .neg = {
      0b00000000,
      0b00000000,
      0b00111100,
      0b00111100,
      0b00111100
    },
    .pos = {
      0b01111110,
      0b10000001,
      0b10000001,
      0b10000001,
      0b10000001
    },
  },
  .maskRight = {
    .neg = {
      0b00111100,
      0b00111100,
      0b00111100,
      0b00000000,
      0b00000000
    },
    .pos = {
      0b10000001,
      0b10000001,
      0b10000001,
      0b10000001,
      0b01111110
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