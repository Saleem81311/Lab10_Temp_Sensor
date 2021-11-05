/*
 * LCD.c
 *
 *  Created on: Nov 4, 2021
 *      Author: tennm
 */

#include <LCD.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void intializeDisplay()             //function to initialize lcd
{
    commandWrite(3);
    delay_ms(10);
    commandWrite(3);
    delay_micro(200);
    commandWrite(3);
    delay_ms(10);

    commandWrite(2);
    delay_micro(100);
    commandWrite(2);
    delay_micro(100);

    commandWrite(8);
    delay_micro(100);
    commandWrite(0x0C);
    delay_micro(100);
    commandWrite(1);
    delay_micro(100);
    commandWrite(6);
    delay_ms(10);
}

void SysTick_Init(){                    //initialize system timer
    SysTick->CTRL &= ~BIT0;             //clears enable to stop the counter
    SysTick->LOAD = 0x00FFFFFF;         //sets the period... note: (3006600/1000 - 1) = 1ms
    SysTick->VAL = 0;                   //clears the value
    SysTick->CTRL = 0x00000005;         //enable SysTick, no uint8_terrupts
}

void pulseEnablePin()                   //pulses enable pin
{
    P4->OUT |=  BIT2;
    delay_ms(10);
    P4->OUT &= ~BIT2;
}

void delay_micro(unsigned micro){       //delays desired time in us
    SysTick->LOAD = micro*3 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = 5;
    while(!(SysTick->CTRL & BIT(16)));
}

void delay_ms(unsigned ms){             //delays desired time in ms
    SysTick->LOAD = ms*3000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = 5;
    while(!(SysTick->CTRL & BIT(16)));
}

void pushNibble(uint8_t nibble)         //pushes 4 bits onto pins
{
    P4->OUT &= (0x0F);
    P4->OUT |= ((nibble & 0x0F) << 4);
    pulseEnablePin();
}

void pushByte(uint8_t byte){            //splits byte into 2 nibbles and sends to push nibble
    pushNibble(byte >> 4);
    pushNibble(byte & (0x0F));
}

void commandWrite(uint8_t command){     //sends byte of command to lcd
    P4->OUT &= ~BIT3;
    delay_ms(10);
    pushByte(command);
}

void dataWrite(uint8_t data){           //sends byte of data to lcd
    P4->OUT |= BIT3;
    delay_ms(10);
    pushByte(data);
}

void printString(char string[]){        //prints a string of characters
    int i;
    for (i = 0; i < (strlen(string)); i++){
            dataWrite(string[i]);
    }
}

