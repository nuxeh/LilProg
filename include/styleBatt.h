#ifndef __STYLE_BATT_H__
#define __STYLE_BATT_H__

#include "style.h"

const style PROG_DECORATOR batt = {
  .maskLeft = {
    .neg = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b11111111
    },
    .pos = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b11111111
    },
  },
  .maskRight = {
    .neg = {
      0b11111111,
      0b00111100,
      0b00111100,
      0b00000000,
      0b00000000
    },
    .pos = {
      0b11111111,
      0b00111100,
      0b00111100,
      0b00000000,
      0b00000000
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
  .offsetLeft = 4,
  .offsetRight = 2
};

#endif