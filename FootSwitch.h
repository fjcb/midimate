#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include "Arduino.h"

class FootSwitch
{
public:
	FootSwitch(int inputPin);
  void update();
private:
	int m_inputPin;
};

#endif
