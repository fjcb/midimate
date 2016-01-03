#include "Arduino.h"
#include "FootSwitch.h"

FootSwitch::FootSwitch(int input_pin, int mode_pin)
 : m_bouncer(Bounce())
 , m_input_pin(input_pin)
 , m_mode_pin(mode_pin)
 , m_state(LOW)
 , m_playing(false)
{
  m_bouncer.attach(m_input_pin);
  m_bouncer.interval(5);
}

bool FootSwitch::stateChanged()
{
  if(m_bouncer.update())
  {
    m_state = m_bouncer.read();
    return true;
  }
  else
  {
    return false;
  }
}

int FootSwitch::triggered()
{
  if(digitalRead(m_mode_pin))
  {
    //touch mode
    if(m_state == HIGH)
    {
      return START;
    }
    else
    {
      return STOP;
    }
  }
  else
  {
    //toggle mode
    int result = HOLD; //no change result

    if(m_state == HIGH)
    {
      if(m_playing)
      {
        //stop
        result = STOP;
        m_playing = false;
      }
      else
      {
        //start
        result = START;
        m_playing = true;
      }    
    }
    
    return result;
  }
}

