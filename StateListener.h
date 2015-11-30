#ifndef STATELISTENER_H
#define STATELISTENER_H

#include "Arduino.h"

class StateListener
{
public:
	StateListener();
  void onChange(bool state);
private:

};

#endif
