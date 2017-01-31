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
