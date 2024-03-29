#include "io.h"
#include "helpers.h"
#include "types.h"

char getcell(Grid *g, int x, int y) {
  if (validposition(g, x, y))
    return g->data[x + (y * g->w)];
  return '.';
}

void setcell(Grid *g, int x, int y, char c) {
  if (validposition(g, x, y) && validcharacter(c))
    g->data[x + (y * g->w)] = c;
}

int gettype(Grid *g, int x, int y) {
  if (validposition(g, x, y))
    return g->type[x + (y * g->w)];
  return 0;
}

void settype(Grid *g, int x, int y, int t) {
  if (validposition(g, x, y))
    g->type[x + (y * g->w)] = t;
}

void setlock(Grid *g, int x, int y) {
  if (validposition(g, x, y)) {
    g->lock[x + (y * g->w)] = 1;
    if (!gettype(g, x, y))
      settype(g, x, y, 1);
  }
}

void setport(Grid *g, int x, int y, char c) {
  setlock(g, x, y);
  settype(g, x, y, 5);
  setcell(g, x, y, c);
}

int getport(Grid *g, int x, int y, int l) {
  if (l) {
    setlock(g, x, y);
    settype(g, x, y, 4);
  } else
    settype(g, x, y, 2);
  return getcell(g, x, y);
}

int getbang(Grid *g, int x, int y) {
  return getcell(g, x - 1, y) == '*' || getcell(g, x + 1, y) == '*' ||
         getcell(g, x, y - 1) == '*' || getcell(g, x, y + 1) == '*';
}
