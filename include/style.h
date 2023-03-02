#ifndef __STYLE_H__
#define __STYLE_H__

#include <Arduino.h>

#ifdef PROGRESS_DATA_IN_PROGMEM
#define PROG_DECORATOR PROGMEM
#else
#define PROG_DECORATOR
#endif

typedef struct {
  uint8_t pos[5];
  uint8_t neg[5];
} mask;

typedef struct {
  mask maskLeft;
  mask maskRight;
  mask maskMid;
  uint8_t offsetLeft;
  uint8_t offsetRight;
} style;

#endif
