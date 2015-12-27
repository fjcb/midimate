#include "ModeSwitch.h"
#include "FootSwitch.h"
#include "MidiManager.h"
#include "StateListener.h"

#define DEBUG

const int ledPin = 4;
const int footSwitchPin = 2;
const int modeSwitchPin = 3;

const int octavePotPin = A0;
const int notePotPin = A1;
const int expPedalPin = A2;

//low b and e, additional octaves
int bs[] = {47, 59, 71, 83};
int es[] = {52, 64, 76, 88};
int velocity = 0x45;
boolean holding = false;
int octaves = 2;

ModeSwitch octaveModeSwitch = ModeSwitch(octavePotPin, 6);
ModeSwitch noteModeSwitch = ModeSwitch(notePotPin, 6);
FootSwitch footSwitchManager = FootSwitch(footSwitchPin, modeSwitchPin);
StateListener stateListener = StateListener();
MidiManager midiManager = MidiManager();


void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(footSwitchPin, INPUT);
  pinMode(modeSwitchPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(footSwitchPin), footSwitch, CHANGE);

  midiManager.setStateListener(stateListener);

#ifdef DEBUG
  Serial.begin(9600);
#else
  Serial.begin(31250);
#endif
}

void loop()
{
#ifdef DEBUG1
  Serial.print("Foot = ");
  Serial.print(digitalRead(footSwitchPin));
  Serial.print("\t Switch = ");
  Serial.print(digitalRead(modeSwitchPin));
  Serial.print("\t Pot 1 Value = ");
  Serial.print(analogRead(octavePotPin));
  Serial.print("\t Pot 1 Mode = ");
  Serial.print(octaveModeSwitch.getMode());
  Serial.print("\t Pot 2 = ");
  Serial.print(analogRead(notePotPin));
  Serial.print("\t Pot 2 Mode = ");
  Serial.print(noteModeSwitch.getMode());
  Serial.print("\t Exp = ");
  Serial.print(analogRead(expPedalPin));
  Serial.print("\n");
#endif 
  

  delay(10);  
}

int run_counter = 0;
void footSwitch()
{
  footSwitchManager.update();

  if(footSwitchManager.stateChanged())
  {
#ifdef DEBUG
  Serial.print("changed ");
  Serial.print(footSwitchManager.getState());
  Serial.print("\n");
#endif
    if(digitalRead(modeSwitchPin))
    {
      //touch mode
      Serial.print("Touch\n");
      digitalWrite(ledPin, footSwitchManager.getState());
    }
    else
    {
      //toggle mode
      Serial.print("Toggle\n");
      run_counter++;
      if(run_counter <= 3)
      {
        digitalWrite(ledPin, HIGH);
      }
      else
      {
        digitalWrite(ledPin, LOW);
        run_counter = 0;
      }
    }
  }
}



void ledStateCallBack(bool state)
{
  digitalWrite(ledPin, state);
}



