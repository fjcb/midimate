#ifndef STATELISTENER_H
#define STATELISTENER_H

#include "Arduino.h"

class StateListener
{
public:
	StateListener(int ledPin);
  void onChange(int state);
private:
  int m_ledPin;

};

#endif
