<PRE>
EEPROM PROGRAMMER INSTRUCTIONS:

on a bare attiny85/45/25/13

PIN 8 -> SDBY_PWR (+5V)
PIN 7 -> one leg of the power switch
PIN 6 -> PWR_ON on atx Supply
PIN 4 -> GND from ATX, and the other leg of the switch.

if uploading from a eeprom programmer for attiny85 use check the following fuses:
low byte: E2
SUT0=0, cksel3=0, cksel2=0, cksel0=0
high byte: DF
SPIEN=0

leave the rest unchecked (ext. and lock bit should be FF)

If after programming you have +5V on pin 7 when applying 5v to
pin 8 and ground to pin 4, the programming was successful.

I recommend cutting the extra legs off splaying the chip out flat and soldering
wires directly to the chips pin, then incase the chip in a 1/2 inch heat
shrink tubing.

see screenshot in attiny85 folder.

You could also upload this using arduino as programmer by compiling and uploading
from arduino.
</PRE>
