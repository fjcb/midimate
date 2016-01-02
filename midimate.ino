#include "ModeSwitch.h"
#include "FootSwitch.h"
#include "MidiManager.h"
#include "StateListener.h"

//#define DEBUG

//digital pins
const int ledPin = 4;
const int footSwitchPin = 2;
const int modeSwitchPin = 3;

//analog pins
const int octavePotPin = A0;
const int notePotPin = A1;
const int expPedalPin = A2;

//midi notes and octaves
const int notes[6][6] = { 
  {40, 52, 64, 76, 88, 100},  //b
  {33, 45, 57, 69, 81, 93},   //e
  {33, 45, 57, 69, 81, 93},   //a
  {38, 50, 62, 74, 86, 98},   //d
  {43, 55, 67, 79, 91, 103},  //g
  {36, 48, 60 ,72, 84, 96}    //c
 };
const int octaves[6][2] = {   //1. start idx, 2. end idx
  {0, 1},   
  {0, 2},
  {0, 3},
  {2, 5},
  {3, 5},
  {4, 5}
 };
int velocity = 0x78;

ModeSwitch octaveModeSwitch = ModeSwitch(octavePotPin, 6);
ModeSwitch noteModeSwitch = ModeSwitch(notePotPin, 6);
FootSwitch footSwitchManager = FootSwitch(footSwitchPin, modeSwitchPin);
StateListener stateListener = StateListener(ledPin);
MidiManager midiManager = MidiManager(stateListener);

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(footSwitchPin, INPUT);
  pinMode(modeSwitchPin, INPUT);

  //attachInterrupt(digitalPinToInterrupt(footSwitchPin), footSwitch, CHANGE);

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

  footSwitch();
  
  delay(5);  
}

int played_octaves_idx = 0;
int played_notes_idx = 0;

void footSwitch()
{
  if(footSwitchManager.stateChanged())
  {
    #ifdef DEBUG
    Serial.print("footswitch state changed\n");
    #endif

    int trigger = footSwitchManager.triggered();
    
    if(trigger == HIGH)
    {
      //play notes
      played_octaves_idx = octaveModeSwitch.getMode();
      played_notes_idx = noteModeSwitch.getMode();
      
      midiManager.playNotes(octaves[played_octaves_idx], notes[played_notes_idx], velocity);

      Serial.print("triggered play notes\n");
    }
    
    if(trigger == LOW)
    {
      //stop notes
      midiManager.stopNotes(octaves[played_octaves_idx], notes[played_notes_idx]);
      Serial.print("triggered stop notes\n");
    }
  }
}


