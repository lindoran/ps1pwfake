PS/1 LPX Soft Power Faker
-------------------------
This is a very simple sketch that watches for a switch press from a PS/1 soft
power switch, such as with the PS/1 2155 or compatible platforms. Useful when
the power supply has been replaced with a standard ATX power supply wired as
an AT power supply (either using an adapter or direct wire).

This should work with most 5V attiny chips and boards but you will need to work
out pin assignments.

on the ML_TINY Board:

PIN 10 -> one leg of the power switch
PIN 09 -> PWR_ON on ATX Supply
PIN +5 -> SDBY_PWR from ATX Supply
PIN GND-> GND from ATX, and the other leg of the switch.

Be sure to insulate all your connections with heat shrink and wrap the
controller in kapton tape (or similar to prevent shorts.

it goes without saying program your controller before hooking up, and
do not apply both +5v from the programer and sdby_pwr from the Power
supply at the same time to prevent damage.

the contacts on old momentary switches are prone to getting dirty.
spray some contact cleaner in and exercise the switch if it's being
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
