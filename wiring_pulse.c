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
