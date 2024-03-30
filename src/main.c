#include <SDL2/SDL.h>
#include <getopt.h>
#include <portmidi.h>
#include <porttime.h>
#include <stdio.h>

#include "constants.h"
#include "draw.h"
#include "globals.h"
#include "helpers.h"
#include "midi.h"
#include "options.h"
#include "theme.h"
#include "triggers.h"
#include "types.h"

/*
Copyright (c) 2020 Devine Lu Linvega

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE.
*/

// Modified by Winter

Document doc;
char clip[CLIPSZ];
MidiNote voices[VOICES];
Rect2d cursor;

int WIDTH = 8 * HOR + PAD * 8 * 2;
int HEIGHT = 8 * (VER + 2) + PAD * 8 * 2;
int BPM = 128, DOWN = 0, ZOOM = 2, PAUSE = 0, GUIDES = 1, MODE = 0;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;
Uint32 *pixels;
PmStream *midi;

int init(void) {
  int i, j;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return error("Init", SDL_GetError());
  gWindow = SDL_CreateWindow(
      "Orca", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * ZOOM,
      HEIGHT * ZOOM, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
  if (gWindow == NULL)
    return error("Window", SDL_GetError());
  gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
  if (gRenderer == NULL)
    return error("Renderer", SDL_GetError());
  gTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
  if (gTexture == NULL)
    return error("Texture", SDL_GetError());
  pixels = (Uint32 *)malloc(WIDTH * HEIGHT * sizeof(Uint32));
  if (pixels == NULL)
    return error("Pixels", "Failed to allocate memory");
  for (i = 0; i < HEIGHT; i++)
    for (j = 0; j < WIDTH; j++)
      pixels[i * WIDTH + j] = theme[0];
  return 1;
}

void usage(void) { // clang-format off
  fprintf(stderr,
          "Usage: orca [options] [file]\n\n"
          "Options:\n"
          "    -d or --midi-device <device>  Sets the midi output device for orca.\n"
          "                                  Default: 0\n"
          "    --list-devices                List available midi devices and exit.\n"
          "    -h or --help                  Print this message and exit.\n");
} // clang-format on

int main(int argc, char *argv[]) {
  int option;
  int device = 0;

  struct option long_options[] = {{"midi-device", required_argument, NULL, 'd'},
                                  {"list-devices", no_argument, NULL, 'l'},
                                  {"help", no_argument, NULL, 'h'},
                                  {NULL, 0, NULL, 0}};

  while ((option = getopt_long(argc, argv, "d:h", long_options, NULL)) != -1) {
    switch (option) {
    case 'd':
      device = atoi(optarg);
      break;
    case 'l':
      for (int i = 0; i < Pm_CountDevices(); ++i) {
        const PmDeviceInfo *device_info = Pm_GetDeviceInfo(i);
        if (device_info->output) {
          printf("#%d - %s\n", i, device_info->name);
        }
      }
      return 0;
    case 'h':
      usage();
      return 0;
    default:
      usage();
      return 0;
    }
  }

  read_theme("theme");

  Uint8 tick = 0;
  if (!init())
    return error("Init", "Failure");
  if (Pm_CountDevices() < 1 || device > Pm_CountDevices() - 1)
    return error("Midi", "Failure");
  initmidi(device);
  if (optind < argc) {
    if (!opendoc(&doc, argv[optind]))
      makedoc(&doc, argv[optind]);
  } else
    makedoc(&doc, "untitled.orca");
  while (1) {
    SDL_Event event;
    double elapsed, start = SDL_GetPerformanceCounter();
    if (!PAUSE) {
      if (tick > 7) {
        frame();
        tick = 0;
      } else
        tick++;
    }
    elapsed = (SDL_GetPerformanceCounter() - start) /
              (double)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(clmp(16.666f - elapsed, 0, 1000));
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
      case SDL_QUIT:
        quit();
        break;
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEMOTION:
        domouse(&event);
        break;
      case SDL_KEYDOWN:
        dokey(&event);
        break;
      case SDL_TEXTINPUT:
        dotext(&event);
        break;
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_EXPOSED)
          redraw(pixels);
        break;
      }
    }
  }
  quit();
  return 0;
}
