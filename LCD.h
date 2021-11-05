/*
 * LCD.h
 *
 *  Created on: Nov 4, 2021
 *      Author: tennm
 */

#ifndef LCD_H_
#define LCD_H_
#include "msp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SysTick_Init();
void pushNibble(uint8_t nibble);
void pulseEnablePin();
void intializeDisplay();
void delay_micro(unsigned micro);
void delay_ms(unsigned ms);
void pushByte(uint8_t byte);
void commandWrite(uint8_t command);
void dataWrite(uint8_t data);
void printString(char string[]);



#endif /* LCD_H_ */
