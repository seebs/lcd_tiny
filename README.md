That Tiny LCD Driver

This is a tiny little LCD driver I built to drive 4x20 character
displays. It's based on Peter Fleury's LCD Library, found at
	http://homepage.hispeed.ch/peterfleury/avr-software.html

This copy of the library has two significant modifications. The
first is the addition of a function to set the custom character
graphics values.  The second is support for the 8-bit mode of the
LCD controller, which lets us skip the fancier 4-bit initialization.
(It's theoretically several microseconds faster, but no one
cares.)

The Fleury code is GPLv3, and insofar as I can do so, I'm releasing
my changes and the associated code into the public domain, as
I really don't feel this is worth copyrighting.

The intended target for this is an Atmega88 or similar chip.
The 8 pins used for data in the LCD controller protocol are
all just PORTD, with PORTC used for the control bits; RS on 2,
RW on 1, and E on 0.

The sample board I made for this just has an Atmega88, a
potentiometer for contrast, an ISP header, and an I2C header
on the standard I2C pins.
