#ifndef THEME_H
#define THEME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COLORS 10

extern Uint32 theme[MAX_COLORS];
void read_theme(const char *filename);

extern int background;

extern int f_high;
extern int f_med;
extern int f_low;
extern int f_inv;

extern int b_high;
extern int b_med;
extern int b_low;
extern int b_inv;

#endif // !THEME_H
