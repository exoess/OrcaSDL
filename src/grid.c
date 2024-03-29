#include "grid.h"
#include "io.h"
#include "operators.h"
#include "types.h"

void initgridframe(Grid *g) {
  int i;
  for (i = 0; i < g->l; ++i) {
    g->lock[i] = 0;
    g->type[i] = 0;
  }
  for (i = 0; i < 36; ++i)
    g->var[i] = '.';
}

int rungrid(Grid *g) {
  int i, x, y;
  initgridframe(g);
  for (i = 0; i < g->l; ++i) {
    char c = g->data[i];
    x = i % g->w;
    y = i / g->w;
    if (c == '.' || g->lock[i])
      continue;
    if (c >= '0' && c <= '9')
      continue;
    if (c >= 'a' && c <= 'z' && !getbang(g, x, y))
      continue;
    operate(g, x, y, c);
  }
  g->f++;
  return 1;
}

void initgrid(Grid *g, int w, int h) {
  int i;
  g->w = w;
  g->h = h;
  g->l = w * h;
  g->f = 0;
  g->r = 1;
  for (i = 0; i < g->l; ++i)
    setcell(g, i % g->w, i / g->w, '.');
  initgridframe(g);
}
