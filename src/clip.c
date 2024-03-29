#include "clip.h"
#include "draw.h"
#include "globals.h"
#include "io.h"
#include "options.h"
#include "types.h"

void copyclip(Rect2d *r, char *c) {
  int x, y, i = 0;
  for (y = 0; y < r->h; ++y) {
    for (x = 0; x < r->w; ++x)
      c[i++] = getcell(&doc.grid, r->x + x, r->y + y);
    c[i++] = '\n';
  }
  c[i] = '\0';
  redraw(pixels);
}

void cutclip(Rect2d *r, char *c) {
  copyclip(r, c);
  insert('.');
}

void pasteclip(Rect2d *r, char *c, int insert) {
  int i = 0, x = r->x, y = r->y;
  char ch;
  while ((ch = c[i++])) {
    if (ch == '\n') {
      x = r->x;
      y++;
    } else {
      setcell(&doc.grid, x, y,
              insert && ch == '.' ? getcell(&doc.grid, x, y) : ch);
      x++;
    }
  }
  doc.unsaved = 1;
  redraw(pixels);
}

void moveclip(Rect2d *r, char *c, int x, int y, int skip) {
  copyclip(r, c);
  insert('.');
  move(x, y, skip);
  pasteclip(r, c, 0);
}
