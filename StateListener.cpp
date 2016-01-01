#include "Arduino.h"
#include "MidiManager.h"

StateListener::StateListener(int ledPin)
 : m_ledPin(ledPin)
{

}

void StateListener::onChange(int state)
{
  digitalWrite(m_ledPin, state); 
}


