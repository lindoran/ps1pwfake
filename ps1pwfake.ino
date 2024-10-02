/*
PS/1 LPX Soft Power Faker
-------------------------
This is a very simple sketch that watches for a switch press from a PS/1 soft
power switch, such as with the PS/1 2155 or compatible platforms. Useful when
the power supply has been replaced with a standard ATX power supply wired as
an AT power supply (either using an adapter or direct wire).


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

#define       PWR_SW             3     // port D3, pin3
#define       PWR_ON             4     // port D3, pin4

bool          PWR_ST           = 0;    // computer is off.
unsigned long debounceDelay    = 50;   // debounce delay in milliseconds
unsigned long longPressDelay   = 3000; // long press delay in milliseconds
unsigned long lastDebounceTime = 0;    // the last time the output pin was toggled
unsigned long buttonPressTime  = 0;    // the time when the button was pressed
bool          longPressActive  = false;// is are we in the middle of a long press.

void setup() {
  bitClear(DDRD, PWR_SW);   // Set switch pin to input
  bitClear(PORTD, PWR_SW);  // input is efectively pulled down by external 10K resistor  

  bitClear(DDRD, PWR_ON);  //Set PWR_ON to input
  bitClear(PORTD, PWR_ON); //clear pullup - input is high Z


}

void loop() {
  // check the status of PWR_SW forever.
   int switchState = bitRead(PIND, PWR_SW); // read the state of the switch into a local variable

  // check if the switch is pressed
  if ((switchState == HIGH) && (longPressActive == false))  {
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTime) > debounceDelay) {
      if (PWR_ST == 0) {
        // if the computer is off, turn it on
        bitSet(DDRD, PWR_ON); // set PWR_ON to output
        bitClear(PORTD, PWR_ON); // ground PWR_ON
        PWR_ST = 1; // update power state
      } else {
        // if the computer is on, check for long press
        if ((currentTime - buttonPressTime) > longPressDelay) {
          bitClear(DDRD, PWR_ON); // set PWR_ON to input (high Z)
          PWR_ST = 0; // update power state
          longPressActive = true;  // We have to wait till the user releases the button
        }
      }
      lastDebounceTime = currentTime; // update the last debounce time
    }
    buttonPressTime = currentTime; // update the button press time
  }
  if((switchState == LOW) && (longPressActive == true)) {
    longPressActive = false;  // if the button is released we can clear this state.
  }

}
