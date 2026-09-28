#include "font.h"

static const uint8_t glyph_a[FONT_HEIGHT] = {
    0b01110,
    0b10001,
    0b10001,
    0b11111,
    0b10001,
    0b10001,
    0b10001
};

const uint8_t *get_glyph(char character)
{
    if (character == 'A') {
        return glyph_a;
    }

    return 0;
}
