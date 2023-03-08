/*
 * LCD.c
 *
 * Created: 2/20/2023 9:44:50 PM
 *  Author: dell
 */ 

#include "LCD.h"

void LCD_4_bit_init(void){
	TIMER0_SetConfig();
	
	DIO_vSetPortDirection(LCD_data_port, OUT); /*set LCD port as output*/
	DIO_vSetPinDirection(LCD_control_port, RS, OUT);
	DIO_vSetPinDirection(LCD_control_port, EN, OUT);
	
	TIMER0_DelayMilliSeconds_with_Blocking(40); /*LCD power on delay*/
	
	LCD_4_bit_sendCommand(0x32); /*4 bit mode*/
	LCD_4_bit_sendCommand(0x28); /*2 line, 5*7 matrix in 4-bit mode*/
	LCD_4_bit_sendCommand(0x0C); /*Display on cursor off*/
	LCD_4_bit_sendCommand(0x06); /*increment cursor*/
	LCD_4_bit_sendCommand(0x01); /*clear display screen*/
}


void LCD_4_bit_sendCommand(uint8 cmnd){
	 /*send higher nibble*/
	DIO_vWritePin(LCD_data_port, D4, getbit(cmnd,4));
	DIO_vWritePin(LCD_data_port, D5, getbit(cmnd,5));
	DIO_vWritePin(LCD_data_port, D6, getbit(cmnd,6));
	DIO_vWritePin(LCD_data_port, D7, getbit(cmnd,7));
	
	
	DIO_vWritePin(LCD_control_port, RS, LOW); /*select command register*/
	
	DIO_vWritePin(LCD_control_port, EN, HIGH); /*enable pulse*/
	TIMER0_DelayMicroSeconds_with_Blocking(1);
	DIO_vWritePin(LCD_control_port, EN, LOW);
	TIMER0_DelayMicroSeconds_with_Blocking(200);
	
	/*send lower nibble*/
	DIO_vWritePin(LCD_data_port, D4, getbit(cmnd,0));
	DIO_vWritePin(LCD_data_port, D5, getbit(cmnd,1));
	DIO_vWritePin(LCD_data_port, D6, getbit(cmnd,2));
	DIO_vWritePin(LCD_data_port, D7, getbit(cmnd,3));
	
	DIO_vWritePin(LCD_control_port, EN, HIGH); /*enable pulse*/
	TIMER0_DelayMicroSeconds_with_Blocking(1);
	DIO_vWritePin(LCD_control_port, EN, LOW);
	TIMER0_DelayMilliSeconds_with_Blocking(4);	
}


void LCD_4_bit_sendChar(uint8 data){
	/*send higher nibble*/
	DIO_vWritePin(LCD_data_port, D4, getbit(data,4));
	DIO_vWritePin(LCD_data_port, D5, getbit(data,5));
	DIO_vWritePin(LCD_data_port, D6, getbit(data,6));
	DIO_vWritePin(LCD_data_port, D7, getbit(data,7));
	
	DIO_vWritePin(LCD_control_port, RS, HIGH); /*select data register*/
	
	DIO_vWritePin(LCD_control_port, EN, HIGH); /*enable pulse*/
	TIMER0_DelayMicroSeconds_with_Blocking(1);
	DIO_vWritePin(LCD_control_port, EN, LOW);
	TIMER0_DelayMicroSeconds_with_Blocking(200);

	/*send lower nibble*/
	DIO_vWritePin(LCD_data_port, D4, getbit(data,0));
	DIO_vWritePin(LCD_data_port, D5, getbit(data,1));
	DIO_vWritePin(LCD_data_port, D6, getbit(data,2));
	DIO_vWritePin(LCD_data_port, D7, getbit(data,3));
	
	DIO_vWritePin(LCD_control_port, EN, HIGH); /*enable pulse*/
	TIMER0_DelayMicroSeconds_with_Blocking(1);
	DIO_vWritePin(LCD_control_port, EN, LOW);
	TIMER0_DelayMilliSeconds_with_Blocking(2);
}


void LCD_4_bit_clear(void){
	LCD_4_bit_sendCommand(0x01); /*clear display screen*/
	LCD_4_bit_sendCommand(0x80); /*cursor at home position*/
}


void LCD_4_bit_sendString(uint8 *data){
	for(uint8 i=0; data[i]; i++)
		LCD_4_bit_sendChar(data[i]);
}

void LCD_4_bit_firstLine(void){
	LCD_4_bit_sendCommand(0x80);
}

void LCD_4_bit_secondLine(void){
	LCD_4_bit_sendCommand(0xC0);
}

void LCD_8_bit_init(void){
	DIO_vSetPortDirection(LCD_data_port, OUT); /*set LCD port as output*/
	DIO_vSetPinDirection(LCD_control_port, RS, OUT);
	DIO_vSetPinDirection(LCD_control_port, EN, OUT);
	
	TIMER0_DelayMilliSeconds_with_Blocking(40); /*LCD power on delay*/
	
	LCD_8_bit_sendCommand(0x34); /*1 line, 5*10 matrix in 8-bit mode*/
	LCD_8_bit_sendCommand(0x0E); /*Display on, cursor blinking*/
	LCD_8_bit_sendCommand(0x06); /*increment cursor*/
	LCD_8_bit_sendCommand(0x01); /*clear display screen*/
	LCD_8_bit_sendCommand(0x80); /*cursor at home position*/
	
}


void LCD_8_bit_sendCommand(uint8 cmnd){
	DIO_vWritePortValue(LCD_data_port, cmnd); /*send command*/
	DIO_vWritePin(LCD_control_port, RS, LOW); /*select command register*/
	
	DIO_vWritePin(LCD_control_port, EN, HIGH); /*enable pulse*/
	TIMER0_DelayMicroSeconds_with_Blocking(1);
	DIO_vWritePin(LCD_control_port, EN, LOW);
	TIMER0_DelayMilliSeconds_with_Blocking(2);

}


void LCD_8_bit_sendChar(uint8 data){
	DIO_vWritePortValue(LCD_data_port, data); /*send character*/
	DIO_vWritePin(LCD_control_port, RS, HIGH); /*select data register*/
	
	DIO_vWritePin(LCD_control_port, EN, HIGH); /*enable pulse*/
	TIMER0_DelayMicroSeconds_with_Blocking(1);
	DIO_vWritePin(LCD_control_port, EN, LOW);
	TIMER0_DelayMilliSeconds_with_Blocking(2);
}


void LCD_8_bit_clear(void){
	LCD_8_bit_sendCommand(0x01); /*clear display screen*/
	LCD_8_bit_sendCommand(0x80); /*cursor at home position*/
}


void LCD_8_bit_sendString(uint8 *data){
	for(uint8 i=0; data[i]; i++)
	LCD_8_bit_sendChar(data[i]);
}

void LCD_8_bit_firstLine(void){
	LCD_8_bit_sendCommand(0x80);
}

void LCD_8_bit_secondLine(void){
	LCD_8_bit_sendCommand(0xC0);
}