#include "Arduino.h"
#include "FootSwitch.h"

FootSwitch::FootSwitch(int input_pin, int mode_pin)
 : m_input_pin(input_pin)
 , m_mode_pin(mode_pin)
 , m_last_micros(micros())
{

}

void FootSwitch::update()
{
  if((long)(micros() - m_last_micros) >= m_debouncing_time * 1000)
  {
    if(m_state == LOW)
    {
      m_state = HIGH;
    }
    else
    {
      m_state = LOW;
    }
    m_last_micros = micros();
  }
  
}

bool FootSwitch::stateChanged()
{
  if(m_state != m_last_state)
  {
    m_last_state = m_state;
    return true;
  }
  else
  {
    return false;
  }
}

int FootSwitch::getState()
{
  return m_state;
}

