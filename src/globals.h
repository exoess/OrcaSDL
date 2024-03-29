#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <portmidi.h>

#include "constants.h"
#include "types.h"

extern Document doc;
extern char clip[CLIPSZ];
extern MidiNote voices[VOICES];
extern Rect2d cursor;

extern int WIDTH;
extern int HEIGHT;
extern int BPM, DOWN, ZOOM, PAUSE, GUIDES, MODE;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern SDL_Texture *gTexture;
extern Uint32 *pixels;
extern PmStream *midi;

#endif // !GLOBALS_H
