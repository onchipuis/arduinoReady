/*
  wiring_pulse.c - pulseIn() function
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
  
  Modified 26 Dicember 2016 by Ckristian Duran for Arduino Open-V
*/

#include "arduino.h"

#define ADDR_GPIO ((unsigned int*)0x1040)
#define EXTERNAL_NUM_INTERRUPTS 32

/* wiring_pulse.c */
unsigned long pulseIn(uint32_t pin, uint32_t state, unsigned long timeout)
{
	return pulseInLong(pin, state, timeout);
}

unsigned long pulseInLong(uint32_t pin, uint32_t state, unsigned long timeout)
{
	unsigned long startMicros = micros();

	// wait for any previous pulse to end
	while (!*(ADDR_GPIO+pin)) {
		if (micros() - startMicros > timeout)
			return 0;
	}

	// wait for the pulse to start
	while (*(ADDR_GPIO+pin)) {
		if (micros() - startMicros > timeout)
			return 0;
	}

	unsigned long start = micros();
	// wait for the pulse to stop
	while (!*(ADDR_GPIO+pin)) {
		if (micros() - startMicros > timeout)
			return 0;
	}
	return micros() - start;
}
