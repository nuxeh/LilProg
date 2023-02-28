#ifndef __STYLE_ROUNDED_H__
#define __STYLE_ROUNDED_H__

#include "style.h"

const style PROG_DECORATOR rounded = {
  .maskLN = {
    0b00000000,
    0b00000000,
    0b00011000,
    0b00111100,
    0b00111100
  },
  .maskLP = {
    0b00111100,
    0b01000010,
    0b10000001,
    0b10000001,
    0b10000001
  },
  .maskRN = {
    0b00111100,
    0b00111100,
    0b00011000,
    0b00000000,
    0b00000000
  },
  .maskRP = {
    0b10000001,
    0b10000001,
    0b10000001,
    0b01000010,
    0b00111100
  },
  .maskMN = {
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100
  },
  .maskMP = {
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001
  },
  .offsetL = 2,
  .offsetR = 2
};

#endif