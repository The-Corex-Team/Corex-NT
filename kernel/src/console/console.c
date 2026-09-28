#include "console.h"
#include <stdint.h>
#include <stddef.h>
#include "font.h"
static struct limine_framebuffer *g_framebuffer = NULL;

void console_init(struct limine_framebuffer *framebuffer)
{
	g_framebuffer = framebuffer;
}

static void put_pixel(size_t x, size_t y, uint32_t color)
{
	if(g_framebuffer == NULL) {
		return;
	}

	if(x >= g_framebuffer->width || y >= g_framebuffer->height){
		return;
	}


	volatile uint32_t *pixels = g_framebuffer->address;

	size_t pixels_per_row = g_framebuffer->pitch / 4;

	pixels[y * pixels_per_row + x] = color;
}

static void fill_rect(
    size_t x,
    size_t y,
    size_t width,
    size_t height,
    uint32_t color
)
{
    for (size_t row = 0; row < height; row++) {
        for (size_t column = 0; column < width; column++) {
            put_pixel(
                x + column,
                y + row,
                color
            );
        }
    }
}

static void draw_glyph(
    const uint8_t *glyph,
    size_t x,
    size_t y,
    size_t scale,
    uint32_t color
)
{
    if (glyph == NULL) {
        return;
    }

    for (size_t row = 0; row < FONT_HEIGHT; row++) {
        for (size_t column = 0; column < FONT_WIDTH; column++) {
            uint8_t bit = glyph[row] &
                (1u << (FONT_WIDTH - 1 - column));

            if (bit != 0) {
                fill_rect(
                    x + column * scale,
                    y + row * scale,
		    scale,
		    scale,
                    color
                );
            }
        }
    }
}

void console_write(const char *text)
{
	if(g_framebuffer == NULL){
		return;
	}

	if(text == NULL) {
		return;
	}

	//volatile uint32_t *pixels = g_framebuffer->address;
	//pixels[0] = 0x00FFFFFF;
	// Commented cause they will not be used anymore. bye bye. but as a start yeah it might help for start in case we break anything :)
	//put_pixel(100, 50, 0x00FFFFFF);
	//fill_rect(100, 50, 100, 50, 0x00FFFFFF);
	
	const uint8_t *glyph = get_glyph('A');

	draw_glyph(glyph, 100, 50, 100, 0x00FFFFFF);
}

