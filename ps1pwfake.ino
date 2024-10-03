/*
PS/1 LPX Soft Power Faker
-------------------------
This is a very simple sketch that watches for a switch press from a PS/1 soft
power switch, such as with the PS/1 2155 or compatible platforms. Useful when
the power supply has been replaced with a standard ATX power supply wired as
an AT power supply (either using an adapter or direct wire).

This should work with most 5V attiny chips and boards but you will need to work 
out pin asignments.

on the ML_TINY Board:

PIN 10 -> one leg of the power switch
PIN 09 -> PWR_ON on ATX Supply 
PIN +5 -> SDBY_PWR from ATX Supply
PIN GND-> GND from ATX, and other leg of the switch.

on a bare attiny85/45/25/13

on a bare attiny85/45/25/13

PIN 8 -> SDBY_PWR (+5V)
PIN 7 -> one leg of the power switch
PIN 6 -> PWR_ON on atx Supply
PIN 4 -> GND from ATX, and the other leg of the switch.

If after programming you have +5V on pin 7 when applying 5v to
pin 8 and ground to pin 4, the programming was successful.

I recommend cutting the extra legs off splaying the chip out flat and soldering
wires directly to the chips pin, then incase the chip in a 1/2 inch heat
shrink tubing.                                                                                    

if uploading from a mini-pro programmer for attiny85 use check the following in fuses:
low byte: E2
SUT0=0, cksel3=0, cksel2=0, cksel0=0
high byte: DF
SPIEN=0

leave the rest unchecked (ext. and lock bit should be FF)
see screenshot in attiny85 folder.


Be sure to insulate all your connections with heat shrink and wrap the 
controler in kapton tape (or similar to prevent shorts.

it goes without saying program your controller before hooking up, and 
do not apply both +5v from the programer and sdby_pwr from the Power
suppy at the same time to prevent damage.

the contacts on old momentary switches are prone to getting dirty.
spray some contact cleaner in and excersize the switch if it's being
intermittent.  A very long debounce delay was used to prevent issues.

MIT License:
Copyright 2025 David Collins
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY
OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

 */

// Pin numbers are the bit position on PORTB -- this should work on MOST attiny chips and 
// boards. 



#define       PWR_SW             2     // port B2, pin10 on ml-tiny, pin 7 on attiny85
#define       PWR_ON             1     // port B1, pin9 on ml-tiny, pin 6 on attiny85 

// power supply standby_pwr to VCC / +5v (pin 8 on attiny85) 
// power supply GND and 2nd switch leg to GND (pin 4 on attiny85) 

// caution! see warning about programer voltages above.

unsigned long debounceDelay    = 150;  // debounce delay in milliseconds
unsigned long lastDebounceTime = 0;    // the last time the output pin was toggled
int           lastSwState      = 1;    // last state of the switch

bool          PWR_ST           = false;// computer is off.
bool          longPressActive  = false;// is are we in the middle of a long press.

void setup() {
  bitClear(DDRB, PWR_SW);   // Set switch pin to input
  bitSet(PORTB, PWR_SW);    // enable internal pullup, switch wired to ground and this pin.
                            // pull up is VERY weak and will pull to ground quickly 

  bitClear(DDRB, PWR_ON);  //Set PWR_ON to input
  bitClear(PORTB, PWR_ON); //clear pullup - input is high Z


}

void loop() {
  // check the status of PWR_SW forever.
   int switchState = bitRead(PINB, PWR_SW); // read the state of the switch into a local variable
    
   // check if switch is not the same as last time, start counter over if so
   if (switchState != lastSwState) {
      lastDebounceTime = millis();
      longPressActive = false;
   }

   // if the switch is down, and has been triggered we wait for it to change back to down again.
   if ((switchState == LOW) && (longPressActive == false)) {
     
      // check to see if its a legitimate button press
      if ((millis() - lastDebounceTime) > debounceDelay) {
        // turn on the computer
        if (PWR_ST == false) {  // is off
           bitSet(DDRB, PWR_ON); // set PWR_ON to output (ground)
           PWR_ST = true; // update power state
           longPressActive = true; // user may still be holding button down
        }
        // turn off the computer
        else {
           bitClear(DDRB, PWR_ON); //set PWR_ON to input (high Z)
           PWR_ST = false; // update power state
           longPressActive = true; // user may still be holding button down
        }
      }
   }
   lastSwState = switchState;    // save the previus state 
}
