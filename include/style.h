#ifndef __STYLE_H__

#include <Arduino.h>

#ifdef PROGRESS_DATA_IN_PROGMEM
#define PROG_DECORATOR PROGMEM
#else
#define PROG_DECORATOR
#endif

typedef uint8_t mask[5];

struct style {
  uint8_t maskLN[5];
  uint8_t maskLP[5];
  uint8_t maskRN[5];
  uint8_t maskRP[5];
  uint8_t maskMN[5];
  uint8_t maskMP[5];
  uint8_t offsetL = 0;
  uint8_t offsetR = 0;
};

typedef struct style style;

#endif
