/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#ifndef __attribute_deprecated__
#define __attribute_deprecated__
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

#include "binary.h"

#ifdef __cplusplus
extern "C"{
#endif

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

// This is inside the start.S
// PLEASE DO NOT USE THEM
int seai(int) __attribute_deprecated__;  // DONE, activates SOME interrupts
int sei(void) __attribute_deprecated__;  // DONE
int cli(void) __attribute_deprecated__;  // DONE
#define interrupts() sei()
#define noInterrupts() cli()

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// This maybe is necesary
#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef bool boolean;
typedef uint8_t byte;

void init(void);
void initVariant(void);

int atexit(void (*func)()) __attribute__((weak));

void pinMode(uint32_t, uint32_t);       // DONE
void digitalWrite(uint32_t, uint32_t);  // DONE
int digitalRead(uint32_t);             // DONE
int analogRead(uint32_t) __attribute_deprecated__;  // DONE
void analogReference(uint32_t mode) __attribute_deprecated__;  // DONE
void analogWrite(uint32_t, int) __attribute_deprecated__;  // DONE

unsigned long millis(void);           // DONE
unsigned long micros(void);           // DONE
void delay(unsigned long);            // DONE
void delayMicroseconds(unsigned int us);    // DONE
unsigned long pulseIn(uint32_t pin, uint32_t state, unsigned long timeout) __attribute_deprecated__;    // DONE
unsigned long pulseInLong(uint32_t pin, uint32_t state, unsigned long timeout) __attribute_deprecated__;// DONE

void shiftOut(uint32_t dataPin, uint32_t clockPin, uint32_t bitOrder, uint32_t val);  // DONE
uint8_t shiftIn(uint32_t dataPin, uint32_t clockPin, uint32_t bitOrder);  // DONE

void attachInterrupt(uint32_t, void (*)(void), int mode);  // DONE
void detachInterrupt(uint32_t);        // DONE

void yield();
void setup();
void loop();

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.

#define analogInPinToBit(P) (P)

#define NOT_A_PIN 0
#define NOT_A_PORT 0

#define NOT_AN_INTERRUPT -1

#ifdef ARDUINO_MAIN
#define PA 1
#define PB 2
#define PC 3
#define PD 4
#define PE 5
#define PF 6
#define PG 7
#define PH 8
#define PJ 10
#define PK 11
#define PL 12
#endif

#define NOT_ON_TIMER 0
#define TIMER0A 1
#define TIMER0B 2
#define TIMER1A 3
#define TIMER1B 4
#define TIMER1C 5
#define TIMER2  6
#define TIMER2A 7
#define TIMER2B 8

#define TIMER3A 9
#define TIMER3B 10
#define TIMER3C 11
#define TIMER4A 12
#define TIMER4B 13
#define TIMER4C 14
#define TIMER4D 15
#define TIMER5A 16
#define TIMER5B 17
#define TIMER5C 18

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include "WCharacter.h"
#include "WString.h"
//#include "HardwareSerial.h"         // NOT SUPPORTED
//#include "USBAPI.h"                 // NOT SUPPORTED

uint16_t makeWord(uint16_t w);  // DONE
uint16_t makeWord(byte h, byte l);  // DONE

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L) __attribute_deprecated__;  // DONE
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L) __attribute_deprecated__;  // DONE

//void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0) __attribute_deprecated__; // NOT SUPPORTED AT ALL
//void noTone(uint8_t _pin) __attribute_deprecated__;

// WMath prototypes
long random(long);  // DONE
long random(long, long);  // DONE
void randomSeed(unsigned long);  // DONE
long map(long, long, long, long, long);  // DONE

#endif

typedef void (*f_int_t) (void); 

extern f_int_t INTERRUPT_TABLE[32];

// Only one model for Open-V
//#include "pins_arduino.h"

#define OPENV_MAX_PINS 8  // No more than this GPIO
#ifndef F_CPU
#define F_CPU 2500000L    // Default for demos
#endif

#endif
