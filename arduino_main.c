/*
  This is the main entry code for Arduino Open-V
  
  First version: 12/30/16 by: Ckristian Duran
*/

#include "arduino.h"

#define ADDR_GPIO ((unsigned int*)0x1040)
#define EXTERNAL_NUM_INTERRUPTS 32

void main(void)
{
  setup();
  while(1)
  {
    loop();
    yield();
  }
}
