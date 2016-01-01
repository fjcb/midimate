#include "Arduino.h"
#include "MidiManager.h"

MidiManager::MidiManager(StateListener stateListener)
 : m_stateListener(stateListener)
{

}

void MidiManager::sendNote(int cmd, int note, int vel)
{
#ifdef DEBUG
  Serial.print("Midi Output");
#else
  Serial.write(cmd);
  Serial.write(note);
  Serial.write(vel);
#endif
}

void MidiManager::playNotes(const int octaves[], const int notes[], int velocity)
{ 
  for(int i = octaves[0]; i <= octaves[1]; i++)
  {
    sendNote(0x90, notes[i], velocity);
  }
  
  notifyStateListener(HIGH);
}

void MidiManager::stopNotes(const int octaves[], const int notes[])
{
  notifyStateListener(LOW);
  
  for(int i = octaves[0]; i <= octaves[1]; i++)
  {
    sendNote(0x90, notes[i], 0x00);
  }
}

void MidiManager::notifyStateListener(int state)
{
  m_stateListener.onChange(state);
}


