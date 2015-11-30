#include <Bounce2.h>
#include "ModeSwitch.h"

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

Bounce footBouncer = Bounce();
ModeSwitch octaveModeSwitch = ModeSwitch(octavePotPin, 6);
ModeSwitch noteModeSwitch = ModeSwitch(notePotPin, 6);

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(footSwitchPin, INPUT);
  pinMode(modeSwitchPin, INPUT);

  footBouncer.attach(footSwitchPin);
  footBouncer.interval(10);

  attachInterrupt(digitalPinToInterrupt(footSwitchPin), footSwitch, CHANGE);

#ifdef DEBUG
  Serial.begin(9600);
#else
  Serial.begin(31250);
#endif
}

void loop()
{
#ifdef DEBUG2
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
  

  delay(3);
  
}

void footSwitch()
{
  //footBouncer.update();
  
#ifdef DEBUG
  Serial.print("down \n");
  Serial.print(digitalRead(footSwitchPin));
#endif
  
  digitalWrite(ledPin, digitalRead(footSwitchPin));
}

void sendNote(int cmd, int note, int vel)
{
#ifndef DEBUG
  Serial.write(cmd);
  Serial.write(note);
  Serial.write(vel);
#endif
}

void stopNotes(int cmd)
{
  holding = false;
  digitalWrite(ledPin, LOW);
  
  for(int i = 0; i < 4; i++)
  {
    sendNote(cmd, bs[i], 0x00);
    sendNote(cmd, es[i], 0x00);
  }
}

void playNotes(int cmd, int noteArray[])
{
  for(int i = 0; i < octaves; i++)
  {
    sendNote(cmd, noteArray[i], velocity);
  }
  digitalWrite(ledPin, HIGH);
}




