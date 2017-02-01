/*
  Part of the Wiring project - http://wiring.uniandes.edu.co

  Copyright (c) 2004-05 Hernando Barragan

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
  
  Modified 24 November 2006 by David A. Mellis
  Modified 1 August 2010 by Mark Sproul
  Modified 26 Dicember 2016 by Ckristian Duran for Arduino Open-V
*/

#include "arduino.h"

#define ADDR_GPIO ((unsigned int*)0x1040)
#define EXTERNAL_NUM_INTERRUPTS 32


#ifdef ENABLE_INTERRUPTS

void dummy_int(void)
{
  // Empty
}

f_int_t INTERRUPT_TABLE[EXTERNAL_NUM_INTERRUPTS] = 
{
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int,
  &dummy_int
};

uint32_t *irq(uint32_t *regs, uint32_t irqs)
{
	for(int i=0; i < 32; i++)
	{
	  if(irqs & (1 << i)) (*INTERRUPT_TABLE[i])();
	}
	
	// This is mandatory for check
	return regs;
}

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {
  if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {
    INTERRUPT_TABLE[interruptNum] = userFunc;
  }
}

void detachInterrupt(uint8_t interruptNum) {
  if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {
    INTERRUPT_TABLE[interruptNum] = &dummy_int;
  }
}

#endif // ENABLE_INTERRUPTS

void yield() {
	// Empty
}
