#include <SDL2/SDL.h>
#include <portmidi.h>
#include <porttime.h>

#include "globals.h"
#include "midi.h"
#include "types.h"

MidiNote *sendmidi(int chn, int val, int vel, int len) {
  int i = 0;
  /* Detrigger */
  for (i = 0; i < VOICES; ++i) {
    MidiNote *n = &voices[i];
    if (!n->len || n->chn != chn || n->val != val)
      continue;
    Pm_WriteShort(midi, Pt_Time(), Pm_Message(0x90 + n->chn, n->val, 0));
    n->len = 0;
  }
  /* Trigger */
  for (i = 0; i < VOICES; ++i) {
    MidiNote *n = &voices[i];
    if (n->len < 1) {
      n->chn = chn;
      n->val = val;
      n->vel = vel;
      n->len = len;
      Pm_WriteShort(midi, Pt_Time(), Pm_Message(0x90 + chn, val, vel * 3));
      return n;
    }
  }
  return NULL;
}

void runmidi(void) {
  int i;
  for (i = 0; i < VOICES; ++i) {
    MidiNote *n = &voices[i];
    if (n->len > 0) {
      n->len--;
      if (n->len == 0)
        Pm_WriteShort(midi, Pt_Time(), Pm_Message(0x90 + n->chn, n->val, 0));
    }
  }
}

void initmidi(int device) {
  int i, id = device % Pm_CountDevices();
  for (i = 0; i < Pm_CountDevices(); ++i) {
    const PmDeviceInfo *device_info = Pm_GetDeviceInfo(i);
    if (device_info->output) {
      printf("#%d - %s (%s)\n", i, device_info->name, i == device ? "*" : " ");
    }
    Pm_OpenOutput(&midi, device, NULL, 128, 0, NULL, 1);
  }
}
