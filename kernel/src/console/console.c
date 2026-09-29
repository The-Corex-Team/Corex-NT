#include "console.h"
#include <stdint.h>
#include <stddef.h>
#include "font.h"
static struct limine_framebuffer *g_framebuffer = NULL;

static size_t cursor_x = 0;
static size_t cursor_y = 0;
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

static void scroll(size_t line_height)
{
    if (g_framebuffer == NULL) {
        return;
    }

    size_t pixels_per_row = g_framebuffer->pitch / 4;

    volatile uint32_t *pixels = g_framebuffer->address;

    for (size_t y = 0; y + line_height < g_framebuffer->height; y++) {
        for (size_t x = 0; x < g_framebuffer->width; x++) {
            pixels[y * pixels_per_row + x] =
                pixels[(y + line_height) * pixels_per_row + x];
        }
    }


    for (size_t y = g_framebuffer->height - line_height;
         y < g_framebuffer->height;
         y++) {

        for (size_t x = 0; x < g_framebuffer->width; x++) {
            pixels[y * pixels_per_row + x] = 0x00000000;
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

static void print(const char *text)
{
    if (text == NULL) {
        return;
    }

	size_t scale = 1;
	size_t character_width = FONT_WIDTH * scale + scale;
	size_t character_height = FONT_HEIGHT * scale;

    for (size_t index = 0; text[index] != '\0'; index++) {

	if (text[index] == '\n') {
		cursor_x = 0;
		cursor_y += FONT_HEIGHT * scale;
		continue;
	}

	if(cursor_x + character_width > g_framebuffer->width){
		cursor_x = 0;
		cursor_y += character_height;
	}

	if (cursor_y + character_height > g_framebuffer->height) {
		scroll(character_height);
		cursor_y -= character_height;
	}

	if(text[index] == ' '){
		cursor_x += FONT_WIDTH * scale + scale;
		continue;
	}


        const uint8_t *glyph = get_glyph(text[index]);

        if (glyph != NULL) {
            draw_glyph(
                glyph,
                cursor_x,
                cursor_y,
                scale,
                0x00FFFFFF
            );
        }

        cursor_x += FONT_WIDTH * scale + scale;
    }
}

void console_write(const char *text)
{
    if (g_framebuffer == NULL) {
        return;
    }

    if (text == NULL) {
        return;
    }

    print(text);
}
