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
