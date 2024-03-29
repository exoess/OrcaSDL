#include <SDL2/SDL.h>

#include "draw.h"
#include "globals.h"
#include "grid.h"
#include "helpers.h"
#include "io.h"
#include "midi.h"
#include "options.h"

int error(char *msg, const char *err) {
  printf("Error %s: %s\n", msg, err);
  return 0;
}

void makedoc(Document *d, char *name) {
  initgrid(&d->grid, HOR, VER);
  d->unsaved = 0;
  scpy(name, d->name, 256);
  redraw(pixels);
  printf("Made: %s\n", name);
}

int opendoc(Document *d, char *name) {
  int x = 0, y = 0;
  char c;
  FILE *f = fopen(name, "r");
  if (!f)
    return error("Load", "Invalid input file");
  initgrid(&d->grid, HOR, VER);
  while ((c = fgetc(f)) != EOF && d->grid.l <= MAXSZ) {
    if (c == '\n') {
      x = 0;
      y++;
    } else {
      setcell(&d->grid, x, y, c);
      x++;
    }
  }
  d->unsaved = 0;
  scpy(name, d->name, 256);
  redraw(pixels);
  printf("Opened: %s\n", name);
  return 1;
}

void savedoc(Document *d, char *name) {
  int x, y;
  FILE *f = fopen(name, "w");
  for (y = 0; y < d->grid.h; ++y) {
    for (x = 0; x < d->grid.w; ++x)
      fputc(getcell(&d->grid, x, y), f);
    fputc('\n', f);
  }
  fclose(f);
  d->unsaved = 0;
  scpy(name, d->name, 256);
  redraw(pixels);
  printf("Saved: %s\n", name);
}

void transform(Rect2d *r, char (*fn)(char)) {
  int x, y;
  for (y = 0; y < r->h; ++y)
    for (x = 0; x < r->w; ++x)
      setcell(&doc.grid, r->x + x, r->y + y,
              fn(getcell(&doc.grid, r->x + x, r->y + y)));
  redraw(pixels);
}

void setoption(int *i, int v) {
  *i = v;
  redraw(pixels);
}

void orcaselect(int x, int y, int w, int h) {
  Rect2d r;
  r.x = clmp(x, 0, HOR - 1);
  r.y = clmp(y, 0, VER - 1);
  r.w = clmp(w, 1, HOR - x);
  r.h = clmp(h, 1, VER - y);
  if (r.x != cursor.x || r.y != cursor.y || r.w != cursor.w ||
      r.h != cursor.h) {
    cursor = r;
    redraw(pixels);
  }
}

void scale(int w, int h, int skip) {
  orcaselect(cursor.x, cursor.y, cursor.w + (w * (skip ? 4 : 1)),
             cursor.h + (h * (skip ? 4 : 1)));
}

void move(int x, int y, int skip) {
  orcaselect(cursor.x + (x * (skip ? 4 : 1)), cursor.y + (y * (skip ? 4 : 1)),
             cursor.w, cursor.h);
}

void reset(void) {
  MODE = 0;
  GUIDES = 1;
  orcaselect(cursor.x, cursor.y, 1, 1);
}

void comment(Rect2d *r) {
  int y;
  char c = getcell(&doc.grid, r->x, r->y) == '#' ? '.' : '#';
  for (y = 0; y < r->h; ++y) {
    setcell(&doc.grid, r->x, r->y + y, c);
    setcell(&doc.grid, r->x + r->w - 1, r->y + y, c);
  }
  doc.unsaved = 1;
  redraw(pixels);
}

void insert(char c) {
  int x, y;
  for (x = 0; x < cursor.w; ++x)
    for (y = 0; y < cursor.h; ++y)
      setcell(&doc.grid, cursor.x + x, cursor.y + y, c);
  if (MODE)
    move(1, 0, 0);
  doc.unsaved = 1;
  redraw(pixels);
}

void frame(void) {
  rungrid(&doc.grid);
  redraw(pixels);
  runmidi();
}

void selectoption(int option) {
  switch (option) {
  case 3:
    orcaselect(cursor.x, cursor.y, 1, 1);
    break;
  case 8:
    PAUSE = 1;
    frame();
    break;
  case 15:
    setoption(&GUIDES, !GUIDES);
    break;
  case HOR - 1:
    savedoc(&doc, doc.name);
    break;
  }
}

void quit(void) {
  free(pixels);
  SDL_DestroyTexture(gTexture);
  gTexture = NULL;
  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
  exit(0);
}
