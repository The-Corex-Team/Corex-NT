#ifndef FONT_H
#define FONT_H

#include <stdint.h>

#define FONT_WIDTH  5
#define FONT_HEIGHT 7

const uint8_t *get_glyph(char character);

#endif
