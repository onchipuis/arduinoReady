/*
  wiring.c - Partial implementation of the Wiring API for the ATmega8.
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

unsigned long millis()
{
	unsigned long m;
#ifdef ENABLE_INTERRUPTS
	uint32_t oldSREG = cli();
#endif // ENABLE_INTERRUPTS
	
	unsigned int num_cycles, num_cyclesh;
	__asm__("rdcycle %0; rdcycleh %1;" : "=r"(num_cycles), "=r"(num_cyclesh));
	
	uint64_t cycles = ((uint64_t)num_cyclesh << 32) | (uint64_t)num_cycles;
	m = cycles * 1000 ; 
	m /= F_CPU ;
	
#ifdef ENABLE_INTERRUPTS
	seai(oldSREG);
#endif // ENABLE_INTERRUPTS

	return m;
}

unsigned long micros() {
	unsigned long m;
#ifdef ENABLE_INTERRUPTS
	uint32_t oldSREG = cli();
#endif // ENABLE_INTERRUPTS
	
	unsigned int num_cycles, num_cyclesh;
	__asm__("rdcycle %0; rdcycleh %1;" : "=r"(num_cycles), "=r"(num_cyclesh));
	
	uint64_t cycles = ((uint64_t)num_cyclesh << 32) | (uint64_t)num_cycles;
	m = cycles * 1000000 ; 
	m /= F_CPU ; 
	
#ifdef ENABLE_INTERRUPTS
	seai(oldSREG);
#endif // ENABLE_INTERRUPTS
	return m;
}

void delay(unsigned long ms)  // HUH
{
  //for(;ms > 0; ms--);
	uint32_t start = micros();

	while (ms > 0) {
		yield();
		while ( ms > 0 && (micros() - start) >= 1000) {
			ms--;
			start += 1000;
		}
	}
}

/* Delay for the given number of microseconds.  Assumes a 2.5 MHz clock. */
void delayMicroseconds(unsigned int us)
{
	// call = 4 cycles + 2 to 4 cycles to init us(2 for constant delay, 4 for variable)

	// there is no delay_us, welcome to hell
	//delay_us(us);
#if F_CPU >= 2500000L
  // for the 2.5MHz clock

	// zero delay fix
	if (!us) return; //  = 3 cycles, (4 when true)

	// the following loop takes a 1.6 of a microsecond (8 cycles)
	// per iteration, so execute it six times for each microsecond of
	// delay requested.
	us = (us << 4) / 10; // >> = 4 cycles + / = ??? cycles

	// account for the time taken in the preceeding commands.
	// we just burned 97 (100) cycles above, remove 94
	us -= 108; //=3 cycles

#else
	// for the 100 MHz internal clock for the aventurous ones, trying to overclock	

#endif

	// busy wait
	__asm__ __volatile__ (
		"1: addi %0,   %0, -1" "\n\t"                 // 3 cycles
		"   bne  zero, %0, 1b" : "=r" (us)            // 5 cycles
	);
	// return = 4 cycles
}

void init()
{
  // dummy
}
