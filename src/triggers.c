#include <SDL2/SDL.h>

#include "clip.h"
#include "globals.h"
#include "helpers.h"
#include "options.h"
#include "triggers.h"

void domouse(SDL_Event *event) {
  int cx = event->motion.x / ZOOM / 8 - PAD;
  int cy = event->motion.y / ZOOM / 8 - PAD;
  switch (event->type) {
  case SDL_MOUSEBUTTONUP:
    DOWN = 0;
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (cy == VER + 1)
      selectoption(cx);
    else {
      orcaselect(cx, cy, 1, 1);
      DOWN = 1;
    }
    break;
  case SDL_MOUSEMOTION:
    if (DOWN)
      orcaselect(cursor.x, cursor.y, cx + 1 - cursor.x, cy + 1 - cursor.y);
    break;
  }
}

void dokey(SDL_Event *event) {
  int shift =
      SDL_GetModState() & KMOD_LSHIFT || SDL_GetModState() & KMOD_RSHIFT;
  int ctrl = SDL_GetModState() & KMOD_LCTRL || SDL_GetModState() & KMOD_RCTRL;
  int alt = SDL_GetModState() & KMOD_LALT || SDL_GetModState() & KMOD_RALT;
  if (ctrl) {
    switch (event->key.keysym.sym) {
    /* Generic */
    case SDLK_n:
      makedoc(&doc, "untitled.orca");
      break;
    case SDLK_r:
      opendoc(&doc, doc.name);
      break;
    case SDLK_s:
      savedoc(&doc, doc.name);
      break;
    case SDLK_h:
      setoption(&GUIDES, !GUIDES);
      break;
    /* Edit */
    case SDLK_i:
      setoption(&MODE, !MODE);
      break;
    case SDLK_a:
      orcaselect(0, 0, doc.grid.w, doc.grid.h);
      break;
    case SDLK_x:
      cutclip(&cursor, clip);
      break;
    case SDLK_c:
      copyclip(&cursor, clip);
      break;
    case SDLK_v:
      pasteclip(&cursor, clip, shift);
      break;
    case SDLK_u:
      transform(&cursor, cuca);
      break;
    case SDLK_l:
      transform(&cursor, clca);
      break;
    case SDLK_LEFTBRACKET:
      transform(&cursor, cinc);
      break;
    case SDLK_RIGHTBRACKET:
      transform(&cursor, cdec);
      break;
    case SDLK_UP:
      moveclip(&cursor, clip, 0, -1, alt);
      break;
    case SDLK_DOWN:
      moveclip(&cursor, clip, 0, 1, alt);
      break;
    case SDLK_LEFT:
      moveclip(&cursor, clip, -1, 0, alt);
      break;
    case SDLK_RIGHT:
      moveclip(&cursor, clip, 1, 0, alt);
      break;
    case SDLK_SLASH:
      comment(&cursor);
      break;
    }
  } else {
    switch (event->key.keysym.sym) {
    case SDLK_ESCAPE:
      reset();
      break;
    case SDLK_PAGEUP:
      setoption(&BPM, BPM + 1);
      break;
    case SDLK_PAGEDOWN:
      setoption(&BPM, BPM - 1);
      break;
    case SDLK_UP:
      shift ? scale(0, -1, alt) : move(0, -1, alt);
      break;
    case SDLK_DOWN:
      shift ? scale(0, 1, alt) : move(0, 1, alt);
      break;
    case SDLK_LEFT:
      shift ? scale(-1, 0, alt) : move(-1, 0, alt);
      break;
    case SDLK_RIGHT:
      shift ? scale(1, 0, alt) : move(1, 0, alt);
      break;
    case SDLK_SPACE:
      if (!MODE)
        setoption(&PAUSE, !PAUSE);
      break;
    case SDLK_BACKSPACE:
      insert('.');
      if (MODE)
        move(-2, 0, alt);
      break;
    }
  }
}

void dotext(SDL_Event *event) {
  int i;
  for (i = 0; i < SDL_TEXTINPUTEVENT_TEXT_SIZE; ++i) {
    char c = event->text.text[i];
    if (c < ' ' || c > '~')
      break;
    insert(c);
  }
}
