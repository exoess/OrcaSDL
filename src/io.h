#ifndef IO_H
#define IO_H

#include "types.h"

char getcell(Grid *g, int x, int y);
void setcell(Grid *g, int x, int y, char c);
int gettype(Grid *g, int x, int y);
void settype(Grid *g, int x, int y, int t);
void setlock(Grid *g, int x, int y);
void setport(Grid *g, int x, int y, char c);
int getport(Grid *g, int x, int y, int l);
int getbang(Grid *g, int x, int y);

#endif // !IO_H
