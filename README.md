# midimate

The idea of the midimate project is to create a simple, arduino-based MIDI controller
to trigger notes on an external synthesizer. The arduino can be mounted in a standard
stompbox.


## Hardware

 - Arduino Nano, ATmega328 (all other should also do it)
 - Pin 0 (TX): serial MIDI communication (see [this][https://www.arduino.cc/en/Tutorial/Midi])
 - Pin 2: Footswitch input
 - Pin 3: Modeswitch input
 - Pin 4: Status LED output
 - Pin A0: Octave selector
 - Pin A1: Note selector
 - Pin A2: Expression pedal input (TODO)