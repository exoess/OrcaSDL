#ifndef MIDI_H
#define MIDI_H

#include "types.h"

MidiNote *sendmidi(int chn, int val, int vel, int len);
void runmidi(void);
void initmidi(int device);

#endif // !MIDI_H
