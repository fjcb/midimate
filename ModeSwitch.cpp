#include "Arduino.h"
#include "ModeSwitch.h"

ModeSwitch::ModeSwitch(int analogPin, int numModes)
 : m_analogPin(analogPin)
{
	m_numModes = max(1, numModes);
	m_step = ANALOG_MAX / numModes;
}

int ModeSwitch::getMode()
{
	int current = analogRead(m_analogPin);
	return min(m_numModes - 1, current / m_step);
}
