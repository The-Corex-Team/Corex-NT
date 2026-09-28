#ifndef COREX_CONSOLE_H
#define COREX_CONSOLE_H

#include <limine.h>

void CorexConsoleInitialize(struct limine_framebuffer *framebuffer);
void CorexConsoleWrite(const char *text);

#endif
