#ifndef HELPERS_H
#define HELPERS_H

#include "types.h"

int clmp(int val, int min, int max);
int cisp(char c);
char cchr(int v, char c);
int cb36(char c);
char cuca(char c);
char clca(char c);
char cinc(char c);
char cdec(char c);
int validposition(Grid *g, int x, int y);
int validcharacter(char c);
int ctbl(char c);
char *scpy(char *src, char *dst, int len);

#endif // !HELPERS_H
