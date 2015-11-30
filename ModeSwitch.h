#ifndef MODESWITCH_H
#define MODESWITCH_H

#include "Arduino.h"

#define ANALOG_MAX 1023

class ModeSwitch
{
public:
	ModeSwitch(int analogPin, int numModes);
	int getMode();
private:
	int m_analogPin;
	int m_numModes;
	int m_step;
};

#endif