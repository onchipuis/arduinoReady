/*
  wiring_digital.c - digital input and output functions
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

// Pin protections are hw-based
int modes = 0;

void pinMode(uint32_t pin, uint32_t mode)
{
  // This is more a software thing
	if(pin >= OPENV_MAX_PINS) return;
	if(mode == 0x2) mode = 0x0; // Here is ALWAYS pulldowns
	
	bitWrite(modes, pin, mode);
}

/* wiring_digital.c */
static void turnOffPWM(uint32_t timer)
{
	// Dummy
}

void digitalWrite(uint32_t pin, uint32_t val)
{
	if(pin >= OPENV_MAX_PINS) return;
	if(!bitRead(modes, pin)) return;
	
	*(ADDR_GPIO+pin) = ((uint32_t)val | 0x2);
}

int digitalRead(uint32_t pin)
{
	if(pin >= OPENV_MAX_PINS) return 0;
	if(bitRead(modes, pin)) return 0;
	
	return (*(ADDR_GPIO+pin))? 1 : 0;
}
