#include "Arduino.h"
#include "MidiManager.h"

MidiManager::MidiManager()
{

}

void MidiManager::setStateListener(StateListener stateListener)
{
  m_stateListener = stateListener;
}

void MidiManager::sendNote(int cmd, int note, int vel)
{
#ifndef DEBUG
  Serial.write(cmd);
  Serial.write(note);
  Serial.write(vel);
#endif
}

void MidiManager::stopNotes(int cmd, int noteArray[])
{
  //holding = false;
  notifyStateListener(LOW);
  
  for(int i = 0; i < 4; i++)
  {
    sendNote(cmd, noteArray[i], 0x00);
  }
}

void MidiManager::playNotes(int cmd, int noteArray[])
{
  for(int i = 0; i < 4; i++)
  {
    sendNote(cmd, noteArray[i], 0x45);
  }
  notifyStateListener(HIGH);
}

void MidiManager::notifyStateListener(bool state)
{

}


