#include <portmidi.h>
#include <stdio.h>

#include "helpers.h"
#include "io.h"
#include "midi.h"
#include "operators.h"
#include "types.h"

void opa(Grid *g, int x, int y, char c) {
  char a = getport(g, x - 1, y, 0);
  char b = getport(g, x + 1, y, 1);
  setport(g, x, y + 1, cchr(cb36(a) + cb36(b), b));
  (void)c;
}

void opb(Grid *g, int x, int y, char c) {
  char a = getport(g, x - 1, y, 0);
  char b = getport(g, x + 1, y, 1);
  setport(g, x, y + 1, cchr(cb36(a) - cb36(b), b));
  (void)c;
}

void opc(Grid *g, int x, int y, char c) {
  char rate = getport(g, x - 1, y, 0);
  char mod = getport(g, x + 1, y, 1);
  int mod_ = cb36(mod);
  int rate_ = cb36(rate);
  if (!rate_)
    rate_ = 1;
  if (!mod_)
    mod_ = 8;
  setport(g, x, y + 1, cchr(g->f / rate_ % mod_, mod));
  (void)c;
}

void opd(Grid *g, int x, int y, char c) {
  char rate = getport(g, x - 1, y, 0);
  char mod = getport(g, x + 1, y, 1);
  int rate_ = cb36(rate);
  int mod_ = cb36(mod);
  if (!rate_)
    rate_ = 1;
  if (!mod_)
    mod_ = 8;
  setport(g, x, y + 1, g->f % (rate_ * mod_) == 0 ? '*' : '.');
  (void)c;
}

void ope(Grid *g, int x, int y, char c) {
  if (x >= g->w - 1 || getcell(g, x + 1, y) != '.')
    setcell(g, x, y, '*');
  else {
    setcell(g, x, y, '.');
    setport(g, x + 1, y, c);
    settype(g, x + 1, y, 0);
  }
  settype(g, x, y, 0);
}

void opf(Grid *g, int x, int y, char c) {
  char a = getport(g, x - 1, y, 0);
  char b = getport(g, x + 1, y, 1);
  setport(g, x, y + 1, a == b ? '*' : '.');
  (void)c;
}

void opg(Grid *g, int x, int y, char c) {
  char px = getport(g, x - 3, y, 0);
  char py = getport(g, x - 2, y, 0);
  char len = getport(g, x - 1, y, 0);
  int i, len_ = cb36(len);
  if (!len_)
    len_ = 1;
  for (i = 0; i < len_; ++i)
    setport(g, x + i + cb36(px), y + 1 + cb36(py), getport(g, x + 1 + i, y, 1));
  (void)c;
}

void oph(Grid *g, int x, int y, char c) {
  getport(g, x, y + 1, 1);
  (void)c;
}

void opi(Grid *g, int x, int y, char c) {
  char rate = getport(g, x - 1, y, 0);
  char mod = getport(g, x + 1, y, 1);
  char val = getport(g, x, y + 1, 1);
  int rate_ = cb36(rate);
  int mod_ = cb36(mod);
  if (!rate_)
    rate_ = 1;
  if (!mod_)
    mod_ = 36;
  setport(g, x, y + 1, cchr((cb36(val) + rate_) % mod_, mod));
  (void)c;
}

void opj(Grid *g, int x, int y, char c) {
  char link = getport(g, x, y - 1, 0);
  int i;
  if (link != c) {
    for (i = 1; y + i < 256; ++i)
      if (getcell(g, x, y + i) != c)
        break;
    setport(g, x, y + i, link);
  }
}

void opk(Grid *g, int x, int y, char c) {
  char len = getport(g, x - 1, y, 0);
  int i, len_ = cb36(len);
  if (!len_)
    len_ = 1;
  for (i = 0; i < len_; ++i) {
    char key = getport(g, x + 1 + i, y, 1);
    if (key != '.')
      setport(g, x + 1 + i, y + 1, g->var[cb36(key)]);
  }
  (void)c;
}

void opl(Grid *g, int x, int y, char c) {
  char a = getport(g, x - 1, y, 0);
  char b = getport(g, x + 1, y, 1);
  setport(g, x, y + 1, cb36(a) < cb36(b) ? a : b);
  (void)c;
}

void opm(Grid *g, int x, int y, char c) {
  char a = getport(g, x - 1, y, 0);
  char b = getport(g, x + 1, y, 1);
  setport(g, x, y + 1, cchr(cb36(a) * cb36(b), b));
  (void)c;
}

void opn(Grid *g, int x, int y, char c) {
  if (y <= 0 || getcell(g, x, y - 1) != '.')
    setcell(g, x, y, '*');
  else {
    setcell(g, x, y, '.');
    setport(g, x, y - 1, c);
    settype(g, x, y - 1, 0);
  }
  settype(g, x, y, 0);
}

void opo(Grid *g, int x, int y, char c) {
  char px = getport(g, x - 2, y, 0);
  char py = getport(g, x - 1, y, 0);
  setport(g, x, y + 1, getport(g, x + 1 + cb36(px), y + cb36(py), 1));
  (void)c;
}

void opp(Grid *g, int x, int y, char c) {
  char key = getport(g, x - 2, y, 0);
  char len = getport(g, x - 1, y, 0);
  char val = getport(g, x + 1, y, 1);
  int i, len_ = cb36(len);
  if (!len_)
    len_ = 1;
  for (i = 0; i < len_; ++i)
    setlock(g, x + i, y + 1);
  setport(g, x + (cb36(key) % len_), y + 1, val);
  (void)c;
}

void opq(Grid *g, int x, int y, char c) {
  char px = getport(g, x - 3, y, 0);
  char py = getport(g, x - 2, y, 0);
  char len = getport(g, x - 1, y, 0);
  int i, len_ = cb36(len);
  if (!len_)
    len_ = 1;
  for (i = 0; i < len_; ++i)
    setport(g, x + 1 - len_ + i, y + 1,
            getport(g, x + 1 + cb36(px) + i, y + cb36(py), 1));
  (void)c;
}

void opr(Grid *g, int x, int y, char c) {
  char min = getport(g, x - 1, y, 0);
  char max = getport(g, x + 1, y, 1);
  int min_ = cb36(min);
  int max_ = cb36(max);
  unsigned int key = (g->r + y * g->w + x) ^ (g->f << 16);
  if (!max_)
    max_ = 36;
  if (min_ == max_)
    min_ = max_ - 1;
  key = (key ^ 61U) ^ (key >> 16);
  key = key + (key << 3);
  key = key ^ (key >> 4);
  key = key * 0x27d4eb2d;
  key = key ^ (key >> 15);
  setport(g, x, y + 1, cchr(key % (max_ - min_) + min_, max));
  (void)c;
}

void ops(Grid *g, int x, int y, char c) {
  if (y >= g->h - 1 || getcell(g, x, y + 1) != '.')
    setcell(g, x, y, '*');
  else {
    setcell(g, x, y, '.');
    setport(g, x, y + 1, c);
    settype(g, x, y + 1, 0);
  }
  settype(g, x, y, 0);
}

void opt(Grid *g, int x, int y, char c) {
  char key = getport(g, x - 2, y, 0);
  char len = getport(g, x - 1, y, 0);
  int i, len_ = cb36(len);
  if (!len_)
    len_ = 1;
  for (i = 0; i < len_; ++i)
    setlock(g, x + 1 + i, y);
  setport(g, x, y + 1, getport(g, x + 1 + (cb36(key) % len_), y, 1));
  (void)c;
}

void opu(Grid *g, int x, int y, char c) {
  char step = getport(g, x - 1, y, 0);
  char max = getport(g, x + 1, y, 1);
  int step_ = cb36(step);
  int max_ = cb36(max);
  int bucket;
  if (!step_)
    step_ = 1;
  if (!max_)
    max_ = 8;
  bucket = (step_ * (g->f + max_ - 1)) % max_ + step_;
  setport(g, x, y + 1, bucket >= max_ ? '*' : '.');
  (void)c;
}

void opv(Grid *g, int x, int y, char c) {
  char w = getport(g, x - 1, y, 0);
  char r = getport(g, x + 1, y, 1);
  if (w != '.')
    g->var[cb36(w)] = r;
  else if (w == '.' && r != '.')
    setport(g, x, y + 1, g->var[cb36(r)]);
  (void)c;
}

void opw(Grid *g, int x, int y, char c) {
  if (x <= 0 || getcell(g, x - 1, y) != '.')
    setcell(g, x, y, '*');
  else {
    setcell(g, x, y, '.');
    setport(g, x - 1, y, c);
    settype(g, x - 1, y, 0);
  }
  settype(g, x, y, 0);
}

void opx(Grid *g, int x, int y, char c) {
  char px = getport(g, x - 2, y, 0);
  char py = getport(g, x - 1, y, 0);
  char val = getport(g, x + 1, y, 1);
  setport(g, x + cb36(px), y + cb36(py) + 1, val);
  (void)c;
}

void opy(Grid *g, int x, int y, char c) {
  char link = getport(g, x - 1, y, 0);
  int i;
  if (link != c) {
    for (i = 1; x + i < 256; ++i)
      if (getcell(g, x + i, y) != c)
        break;
    setport(g, x + i, y, link);
  }
}

void opz(Grid *g, int x, int y, char c) {
  char rate = getport(g, x - 1, y, 0);
  char target = getport(g, x + 1, y, 1);
  char val = getport(g, x, y + 1, 1);
  int rate_ = cb36(rate);
  int target_ = cb36(target);
  int val_ = cb36(val);
  int mod;
  if (!rate_)
    rate_ = 1;
  mod = val_ <= target_ - rate_   ? rate_
        : val_ >= target_ + rate_ ? -rate_
                                  : target_ - val_;
  setport(g, x, y + 1, cchr(val_ + mod, target));
  (void)c;
}

void opcomment(Grid *g, int x, int y) {
  int i;
  for (i = 1; x + i < 256; ++i) {
    setlock(g, x + i, y);
    if (getcell(g, x + i, y) == '#')
      break;
  }
  settype(g, x, y, 1);
}

void opmidi(Grid *g, int x, int y) {
  int chn, oct, nte, vel, len;
  chn = cb36(getport(g, x + 1, y, 1));
  if (chn == '.')
    return;
  oct = cb36(getport(g, x + 2, y, 1));
  if (oct == '.')
    return;
  nte = getport(g, x + 3, y, 1);
  if (cisp(nte))
    return;
  vel = getport(g, x + 4, y, 1);
  if (vel == '.')
    vel = 'z';
  len = getport(g, x + 5, y, 1);
  if (getbang(g, x, y)) {
    sendmidi(clmp(chn, 0, 16), 12 * oct + ctbl(nte), clmp(cb36(vel), 0, 36),
             clmp(cb36(len), 1, 36));
    settype(g, x, y, 3);
  } else
    settype(g, x, y, 2);
}

void operate(Grid *g, int x, int y, char c) {
  settype(g, x, y, 3);
  switch (clca(c)) {
  case 'a':
    opa(g, x, y, c);
    break;
  case 'b':
    opb(g, x, y, c);
    break;
  case 'c':
    opc(g, x, y, c);
    break;
  case 'd':
    opd(g, x, y, c);
    break;
  case 'e':
    ope(g, x, y, c);
    break;
  case 'f':
    opf(g, x, y, c);
    break;
  case 'g':
    opg(g, x, y, c);
    break;
  case 'h':
    oph(g, x, y, c);
    break;
  case 'i':
    opi(g, x, y, c);
    break;
  case 'k':
    opk(g, x, y, c);
    break;
  case 'j':
    opj(g, x, y, c);
    break;
  case 'l':
    opl(g, x, y, c);
    break;
  case 'm':
    opm(g, x, y, c);
    break;
  case 'n':
    opn(g, x, y, c);
    break;
  case 'o':
    opo(g, x, y, c);
    break;
  case 'p':
    opp(g, x, y, c);
    break;
  case 'q':
    opq(g, x, y, c);
    break;
  case 'r':
    opr(g, x, y, c);
    break;
  case 's':
    ops(g, x, y, c);
    break;
  case 't':
    opt(g, x, y, c);
    break;
  case 'u':
    opu(g, x, y, c);
    break;
  case 'v':
    opv(g, x, y, c);
    break;
  case 'w':
    opw(g, x, y, c);
    break;
  case 'x':
    opx(g, x, y, c);
    break;
  case 'y':
    opy(g, x, y, c);
    break;
  case 'z':
    opz(g, x, y, c);
    break;
  case '*':
    setcell(g, x, y, '.');
    break;
  case '#':
    opcomment(g, x, y);
    break;
  case ':':
    opmidi(g, x, y);
    break;
  default:
    printf("Unknown operator[%d,%d]: %c\n", x, y, c);
  }
}
