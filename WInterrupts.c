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
