#include <Bounce2.h>

#define DEBUG

const int ledPin = 4;
const int footSwitchPin = 2;
const int modeSwitchPin = 3;

const int octavePotPin = A0;
const int notePotPin = A1;
const int expPedalPin = A2;

Bounce footBouncer = Bounce();

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(footSwitchPin, INPUT);
  pinMode(modeSwitchPin, INPUT);

  footBouncer.attach(footSwitchPin);
  footBouncer.interval(5);

#ifdef DEBUG
  Serial.begin(9600);
#else

#endif
}

void loop()
{
#ifdef DEBUG
  Serial.print("Foot = ");
  Serial.print(digitalRead(footSwitchPin));
  Serial.print("\t Switch = ");
  Serial.print(digitalRead(modeSwitchPin));
  Serial.print("\t Pot 1 = ");
  Serial.print(analogRead(octavePotPin));
  Serial.print("\t Pot 2 = ");
  Serial.print(analogRead(notePotPin));
  Serial.print("\t Exp = ");
  Serial.print(analogRead(expPedalPin));
  Serial.print("\n");
#endif

  footBouncer.update();
  int value = footBouncer.read();
  digitalWrite(ledPin, value && digitalRead(modeSwitchPin));

  delay(10);
  
}


