/*
 * Keypad.h
 *
 * Created: 2/19/2023 10:30:01 AM
 *  Author: dell
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../MCAL/Timer0/Timer0_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#define notPressed 0xFF //returned if no key is pressed

#define debounce_delay 10 //debouncing delay in milliseconds


#define numberOfRows 4
#define numberOfColns 4

#define rowsPort PORT_C
#define colnsPort PORT_D

#define row1 PIN5
#define row2 PIN4
#define row3 PIN3
#define row4 PIN2
#define col1 PIN7
#define col2 PIN6
#define col3 PIN5
#define col4 PIN3

static uint8 rows[] = {row1, row2, row3, row4};
static uint8 colns[] = {col1, col2, col3, col4}; 

void keypadInit();
uint8 keypadGetPressed();
uint8 debounce(uint8 value);


#endif /* KEYPAD_H_ */