#ifndef CLIP_H
#define CLIP_H

#include "types.h"

void copyclip(Rect2d *r, char *c);
void cutclip(Rect2d *r, char *c);
void pasteclip(Rect2d *r, char *c, int insert);
void moveclip(Rect2d *r, char *c, int x, int y, int skip);

#endif // !CLIP_H
