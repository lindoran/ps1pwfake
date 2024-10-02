PS/1 LPX Soft Power Faker
-------------------------
This is a very simple sketch that watches for a switch press from a PS/1 soft
power switch, such as with the PS/1 2155 or compatible platforms. Useful when
the power supply has been replaced with a standard ATX power supply wired as
an AT power supply (either using an adapter or direct wire).


Lack of schematics leaves us without the ability to repair the soft power
circuit on the motherboard, or within the Aztek power supply. This simply
allows us to connect the PWR_ON signal of an ATX power supply to ground,
remembers the state and keeps it grounded until the switch is pressed again
and held by the user for 3 seconds.


This is by no means meant to be a replacement for a proper APM circuit, this
just handles a momentary switch for turning on and off an ATX power supply
in a way that is very similar to the way certain LPX cases like the PS/1
2155 has. 


For this we use a ML-TINY Controller board which has an attiny88
microcontroller, but any attiny or other small arduino board would do with
changes to the pin assignments.  We use digital port reads and writes to
PORTD for this version.


You can find these on ali-express, amazon and ebay for very cheap:
https://www.amazon.com/AITRIP-Development-Digispark-ATmega328-Compatible/dp/B09DY7Y4DL/
https://www.aliexpress.us/item/3256804378194700.html
https://www.ebay.com/itm/314965702332




 - The switch needs to be connected to the +5 pin and D3, we tie D3 to ground
   with a 10k resistor, you can solder this to the back of the board.
  - 5v_Stdby and ground can be connected at the ICSP to the respective pins
   associated. Note you will need to program the controller first via ICSP
   or USB first.
      
       (USB Drivers were not reliably working for these boards for some
        time, ICSP might be the only way to program them properly. you
        can use a TinyASP or arduino as ISP to program.)


 - PWR_ON should be connected to D4.
In setup the sketch sets PWR_ON (D4), and SWITCH (D3) to an input with no pullup
to effectively put it into high Z. 


The main loop of the sketch keeps track of the switch press, by checking for
high levels on D3 and grounds out the PWR_ON (D4) pin if the button is pressed
after a de-bouncing period has passed.


The sketch waits for a second button press of 3 seconds or longer and then sets
PWR_ON to tri-state by switching back to an input with no pull up (high Z).
It waits until the user has released the button, and then waits to be turned on
again.
I recommend extending the pins with small wires and soldering heat shrinking
them to the wires which will need to be cut from the supply plug as they will
not typically flow through the adapter cable if used. Despite the same sizing
used on most power supplies, you do not need giant gauge wires for these
signals.  All levels are 5V TTL.


Insulate the entire controller with kapton or similar tape, to prevent shorting.
be careful to not tape down the reset button on the middle of the controller.
if desired it can be removed using a soldering iron to gently brush it off the
board by heating the pins on both sides.


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