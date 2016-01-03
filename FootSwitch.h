#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include "Arduino.h"
#include <Bounce2.h>

#define START 1
#define STOP 0
#define HOLD 2

class FootSwitch
{
public:
	FootSwitch(int input_pin, int mode_pin);
  bool stateChanged();
  int triggered();
private:
  Bounce m_bouncer;
	int m_input_pin;
  int m_mode_pin;
  int m_state = LOW;
  bool m_playing;
};

#endif
