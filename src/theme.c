#include "theme.h"

Uint32 theme[MAX_COLORS];
void read_theme(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening theme file.\n");
    exit(1);
  }

  int count = 0;
  char hex_color[10];
  while (fscanf(file, "%10s", hex_color) == 1 && count < MAX_COLORS) {
    theme[count++] = (Uint32)strtol(hex_color, NULL, 16);
  }

  fclose(file);
}

int background = 0;

int f_high = 1;
int f_med = 2;
int f_low = 3;
int f_inv = 4;

int b_high = 5;
int b_med = 6;
int b_low = 7;
int b_inv = 8;
