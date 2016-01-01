#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H

#include "Arduino.h"
#include "StateListener.h"

class MidiManager
{
public:
	MidiManager(StateListener stateListener);
  void playNotes(const int* octaves, const int* notes, int velocity);
  void stopNotes(const int* octaves, const int* notes);
private:
  void sendNote(int cmd, int note, int velocity);
  void notifyStateListener(int state);
  StateListener m_stateListener;
};

#endif
