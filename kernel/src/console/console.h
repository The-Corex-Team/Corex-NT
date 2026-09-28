#ifndef CONSOLE_H
#define CONSOLE_H

#include <limine.h>

void console_init(struct limine_framebuffer *framebuffer);
void console_write(const char *text);

#endif
