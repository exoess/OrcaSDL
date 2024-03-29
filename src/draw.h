#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

int getfont(int x, int y, char c, int type, int sel);
void setpixel(Uint32 *dst, int x, int y, int color);
void drawicon(Uint32 *dst, int x, int y, Uint8 *icon, int fg, int bg);
void drawui(Uint32 *dst);
void redraw(Uint32 *dst);

#endif // !DRAW_H
