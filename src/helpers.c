#include <stdlib.h>

#include "helpers.h"
#include "types.h"

int clmp(int val, int min, int max) {
  return (val >= min) ? (val <= max) ? val : max : min;
}

int cisp(char c) { return c == '.' || c == ':' || c == '#' || c == '*'; }

char cchr(int v, char c) {
  v = abs(v % 36);
  if (v >= 0 && v <= 9)
    return '0' + v;
  return (c >= 'A' && c <= 'Z' ? 'A' : 'a') + v - 10;
}

int cb36(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'A' && c <= 'Z')
    return c - 'A' + 10;
  if (c >= 'a' && c <= 'z')
    return c - 'a' + 10;
  return 0;
}

char cuca(char c) { return c >= 'a' && c <= 'z' ? 'A' + c - 'a' : c; }

char clca(char c) { return c >= 'A' && c <= 'Z' ? 'a' + c - 'A' : c; }

char cinc(char c) { return !cisp(c) ? cchr(cb36(c) + 1, c) : c; }

char cdec(char c) { return !cisp(c) ? cchr(cb36(c) - 1, c) : c; }

int validposition(Grid *g, int x, int y) {
  return x >= 0 && x <= g->w - 1 && y >= 0 && y <= g->h - 1;
}

int validcharacter(char c) { return cb36(c) || c == '0' || cisp(c); }

int ctbl(char c) {
  int sharp, uc, deg, notes[] = {0, 2, 4, 5, 7, 9, 11};
  if (c >= '0' && c <= '9')
    return c - '0';
  sharp = c >= 'a' && c <= 'z';
  uc = sharp ? c - 'a' + 'A' : c;
  deg = uc <= 'B' ? 'G' - 'B' + uc - 'A' : uc - 'C';
  return deg / 7 * 12 + notes[deg % 7] + sharp;
}

char *scpy(char *src, char *dst, int len) {
  int i = 0;
  while ((dst[i] = src[i]) && i < len - 2)
    i++;
  dst[i + 1] = '\0';
  return dst;
}
