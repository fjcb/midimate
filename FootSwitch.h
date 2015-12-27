#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include "Arduino.h"

class FootSwitch
{
public:
	FootSwitch(int input_pin, int mode_pin);
  void update();
  bool stateChanged();
  int getState();
private:
	int m_input_pin;
  int m_mode_pin;
  int m_state = LOW;
  int m_last_state = LOW;
  unsigned long m_last_micros;
  const long m_debouncing_time = 35;
};

#endif
