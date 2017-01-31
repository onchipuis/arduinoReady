#include "arduino.h"

#define ADDR_GPIO ((unsigned int*)0x1040)
#define EXTERNAL_NUM_INTERRUPTS 32

/* wiring_shift.c */
uint8_t shiftIn(uint32_t dataPin, uint32_t clockPin, uint32_t bitOrder) {
	uint32_t value = 0;
	uint32_t i;

	for (i = 0; i < 8; ++i) {
		digitalWrite(clockPin, HIGH);
		if (bitOrder == LSBFIRST)
			value |= digitalRead(dataPin) << i;
		else
			value |= digitalRead(dataPin) << (7 - i);
		digitalWrite(clockPin, LOW);
	}
	return value;
}

void shiftOut(uint32_t dataPin, uint32_t clockPin, uint32_t bitOrder, uint32_t val)
{
	uint32_t i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST)
			digitalWrite(dataPin, !!(val & (1 << i)));
		else	
			digitalWrite(dataPin, !!(val & (1 << (7 - i))));
			
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);		
	}
}
