#include <SDL2/SDL.h>

#include "draw.h"
#include "font.h"
#include "globals.h"
#include "helpers.h"
#include "icons.h"
#include "io.h"
#include "theme.h"

int getfont(int x, int y, char c, int type, int sel) {
  if (c >= 'A' && c <= 'Z')
    return c - 'A' + 36;
  if (c >= 'a' && c <= 'z')
    return c - 'a' + 10;
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c == '*')
    return 62;
  if (c == '#')
    return 63;
  if (c == ':')
    return 65;
  if (cursor.x == x && cursor.y == y)
    return 66;
  if (GUIDES) {
    if (x % 8 == 0 && y % 8 == 0)
      return 68;
    if (sel || type || (x % 2 == 0 && y % 2 == 0))
      return 64;
  }
  return 70;
}

void setpixel(Uint32 *dst, int x, int y, int color) {
  if (x >= 0 && x < WIDTH - 8 && y >= 0 && y < HEIGHT - 8)
    dst[(y + PAD * 8) * WIDTH + (x + PAD * 8)] = theme[color];
}

void drawicon(Uint32 *dst, int x, int y, Uint8 *icon, int fg, int bg) {
  int v, h;
  for (v = 0; v < 8; v++)
    for (h = 0; h < 8; h++) {
      int clr = (icon[v] >> (7 - h)) & 0x1;
      setpixel(dst, x + h, y + v, clr == 1 ? fg : bg);
    }
}

void drawui(Uint32 *dst) {
  int i, n = 0, bottom = VER * 8 + 8;

  // cursor
  drawicon(dst, 0 * 8, bottom, font[cursor.x % 36], f_high, background);
  drawicon(dst, 1 * 8, bottom, font[68], f_high, background);
  drawicon(dst, 2 * 8, bottom, font[cursor.y % 36], f_high, background);
  drawicon(dst, 3 * 8, bottom, icons[2],
           cursor.w > 1 || cursor.h > 1 ? b_inv : f_med, background);

  // frame
  drawicon(dst, 5 * 8, bottom, font[(doc.grid.f / 1296) % 36], f_high,
           background);
  drawicon(dst, 6 * 8, bottom, font[(doc.grid.f / 36) % 36], f_high,
           background);
  drawicon(dst, 7 * 8, bottom, font[doc.grid.f % 36], f_high, background);
  drawicon(dst, 8 * 8, bottom, icons[PAUSE ? 1 : 0],
           (doc.grid.f - 1) % 8 == 0 ? b_med : f_med, background);

  // speed
  drawicon(dst, 10 * 8, bottom, font[(BPM / 100) % 10], f_high, background);
  drawicon(dst, 11 * 8, bottom, font[(BPM / 10) % 10], f_high, background);
  drawicon(dst, 12 * 8, bottom, font[BPM % 10], f_high, background);

  // io
  for (i = 0; i < VOICES; ++i)
    if (voices[i].len)
      n++;
  drawicon(dst, 13 * 8, bottom, n > 0 ? icons[2 + clmp(n, 0, 6)] : font[70],
           b_med, background);

  // generics
  drawicon(dst, 15 * 8, bottom, icons[GUIDES ? 10 : 9], GUIDES ? f_high : b_med,
           background);
  drawicon(dst, (HOR - 1) * 8, bottom, icons[11], doc.unsaved ? b_med : f_med,
           background);
}

void redraw(Uint32 *dst) {
  int x, y;
  Rect2d *r = &cursor;
  for (y = 0; y < VER; ++y) {
    for (x = 0; x < HOR; ++x) {
      int sel = x < r->x + r->w && x >= r->x && y < r->y + r->h && y >= r->y;
      int t = gettype(&doc.grid, x, y);
      Uint8 *letter = font[getfont(x, y, getcell(&doc.grid, x, y), t, sel)];
      int fg = background, bg = background;
      if ((sel && !MODE) || (sel && MODE && doc.grid.f % 2)) {
        fg = background;
        bg = b_inv;
      } else {
        switch (t) {
        case 1:
          fg = f_med;
          break;
        case 2:
          fg = f_high;
          break;
        case 3:
          bg = f_high;
          break;
        case 4:
          fg = b_med;
          break;
        case 5:
          bg = b_med;
          break;
        default:
          fg = f_med;
        }
      }
      drawicon(dst, x * 8, y * 8, letter, fg, bg);
    }
  }
  drawui(dst);
  SDL_UpdateTexture(gTexture, NULL, dst, WIDTH * sizeof(Uint32));
  SDL_RenderClear(gRenderer);
  SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
  SDL_RenderPresent(gRenderer);
}
