#ifndef OPTIONS_H
#define OPTIONS_H

#include "types.h"

int error(char *msg, const char *err);
void makedoc(Document *d, char *name);
int opendoc(Document *d, char *name);
void savedoc(Document *d, char *name);
void transform(Rect2d *r, char (*fn)(char));
void setoption(int *i, int v);
void orcaselect(int x, int y, int w, int h);
void scale(int w, int h, int skip);
void move(int x, int y, int skip);
void reset(void);
void comment(Rect2d *r);
void insert(char c);
void frame(void);
void selectoption(int option);
void quit(void);

#endif // !OPTIONS_H
