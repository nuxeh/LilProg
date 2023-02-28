#ifndef __STYLE_H__

#include <Arduino.h>

#ifdef PROGRESS_DATA_IN_PROGMEM
#define PROG_DECORATOR PROGMEM
#else
#define PROG_DECORATOR
#endif

typedef uint8_t mask[5];

struct barStyle {
  mask maskLN[5];
  mask maskLP[5];
  mask maskRN[5];
  mask maskRP[5];
  mask maskMN[5];
  mask maskMP[5];
  uint8_t offsetL = 0;
  uint8_t offsetR = 0;
};

typedef struct barStyle style;

#endif
