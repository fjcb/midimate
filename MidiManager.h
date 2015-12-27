#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H

#include "Arduino.h"
#include "StateListener.h"

class MidiManager
{
public:
	MidiManager();
  void setStateListener(StateListener stateListener);
  void playNotes(int cmd, int* notes);
  void stopNotes(int cmd, int* notes);
private:
  void sendNote(int cmd, int note, int velocity);
  void notifyStateListener(bool state);
  StateListener m_stateListener;
};

#endif
