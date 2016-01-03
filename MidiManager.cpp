#include "Arduino.h"
#include "MidiManager.h"

MidiManager::MidiManager(StateListener stateListener)
 : m_stateListener(stateListener)
{

}

void MidiManager::sendNote(int cmd, int note, int vel)
{
  Serial.write(cmd);
  Serial.write(note);
  Serial.write(vel);
}

void MidiManager::playNotes(const int octaves[], const int notes[], int velocity)
{ 
  for(int i = octaves[0]; i <= octaves[1]; i++)
  {
    sendNote(0x90, min(notes[i], 127), min(velocity, 127));   //0x90 note on for midichannel 0
  }
  
  notifyStateListener(HIGH);
}

void MidiManager::stopNotes(const int octaves[], const int notes[])
{
  notifyStateListener(LOW);
  
  for(int i = octaves[0]; i <= octaves[1]; i++)
  {
    sendNote(0x80, min(notes[i], 127), 0x00);     //0x80 note off for midichannel 0
  }
}

void MidiManager::notifyStateListener(int state)
{
  m_stateListener.onChange(state);
}


