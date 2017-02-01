/*
  wiring_analog.c - analog input and output
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  Modified 28 September 2010 by Mark Sproul
  Modified 26 Dicember 2016 by Ckristian Duran for Arduino Open-V
*/

#include "arduino.h"

#define ADDR_GPIO ((unsigned int*)0x1040)
#define EXTERNAL_NUM_INTERRUPTS 32

/* wiring_analog.c */
uint32_t analog_reference = 0; // TODO: fix this

void analogReference(uint32_t mode)
{
	analog_reference = mode;
}

int analogRead(uint32_t pin)
{
  // ADC not working, but STILL will return the result
  // dammit Luis Rueda, dammit Chaparro
	return (*(unsigned int*)0x1020);
}

void analogWrite(uint32_t pin, int val)
{
	pinMode(pin, OUTPUT);
	if (val == 0)
	{
		digitalWrite(pin, LOW);
	}
	else if (val == 255)
	{
		digitalWrite(pin, HIGH);
	}
	else
	{
		// NOPE (dammit Giovanny)
		// DAMMIT CKDUR, you're so useless
		// Why in the hell you disconnected the irqs?
	}
}
