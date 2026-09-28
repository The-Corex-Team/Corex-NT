#include "console.h"
#include <stdint.h>
#include <stddef.h>
static struct limine_framebuffer *g_framebuffer = NULL;

void CorexConsoleInitialize(struct limine_framebuffer *framebuffer)
{
	g_framebuffer = framebuffer;
}

static void CorexConsolePutPixel(size_t x, size_t y, uint32_t color)
{
	volatile uint32_t *pixels = g_framebuffer->address;

	size_t pixels_per_row = g_framebuffer->pitch / 4;

	pixels[y * pixels_per_row + x] = color;
}

static void CorexConsoleFillRect(
    size_t x,
    size_t y,
    size_t width,
    size_t height,
    uint32_t color
)
{
    for (size_t row = 0; row < height; row++) {
        for (size_t column = 0; column < width; column++) {
            CorexConsolePutPixel(
                x + column,
                y + row,
                color
            );
        }
    }
}

void CorexConsoleWrite(const char *text)
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
	//CorexConsolePutPixel(100, 50, 0x00FFFFFF);
	CorexConsoleFillRect(100, 50, 100, 50, 0x00FFFFFF);
}

