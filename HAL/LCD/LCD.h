/*
 * LCD.h
 *
 * Created: 2/20/2023 9:44:34 PM
 *  Author: dell
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/Timer0/Timer0_Interface.h"
#include <avr/delay.h>

#define LCD_data_port PORT_B
#define LCD_control_port PORT_A
#define RS PIN3
#define EN PIN2
#define D4 PIN0
#define D5 PIN1
#define D6 PIN2
#define D7 PIN4


void LCD_4_bit_init(void);
void LCD_4_bit_sendCommand(uint8 cmnd);
void LCD_4_bit_sendChar(uint8 data);
void LCD_4_bit_clear(void);
void LCD_4_bit_sendString(uint8 *data);
void LCD_4_bit_firstLine(void);
void LCD_4_bit_secondLine(void);

void LCD_8_bit_init(void);
void LCD_8_bit_sendCommand(uint8 cmnd);
void LCD_8_bit_sendChar(uint8 data);
void LCD_8_bit_clear(void);
void LCD_8_bit_sendString(uint8 *data);
void LCD_8_bit_firstLine(void);
void LCD_8_bit_secondLine(void);
#endif /* LCD_H_ */