#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

typedef unsigned char Uint8;

typedef struct {
  int w, h, l, f, r;
  Uint8 var[36], data[MAXSZ], lock[MAXSZ], type[MAXSZ];
} Grid;

typedef struct {
  int unsaved;
  char name[256];
  Grid grid;
} Document;

typedef struct {
  int x, y, w, h;
} Rect2d;

typedef struct {
  int chn, val, vel, len;
} MidiNote;

#endif // !TYPES_H
