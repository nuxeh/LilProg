#ifndef __STYLE_H__

#include <Arduino.h>

#ifdef PROGRESS_DATA_IN_PROGMEM
#define PROG_DECORATOR PROGMEM
#else
#define PROG_DECORATOR
#endif

typedef uint8_t mask[5];

typedef struct {
  mask maskLN;
  mask maskLP;
  mask maskRN;
  mask maskRP;
  mask maskMN;
  mask maskMP;
  uint8_t offsetL = 0;
  uint8_t offsetR = 0;
} style;

#endif
