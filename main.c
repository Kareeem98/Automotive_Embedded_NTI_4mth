/*
 * main.c
 *
 * Created: 2/23/2023 1:27:50 AM
 * Author : kareem
 */ 
#include "MCAL/UART/UART_Interface.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/SPI/SPI_Interface.h"

int main(void)
{
	SPI_init();
	UART_init(9600);
	
	uint8 data ;
	
	
	while (1)
	{
		
		data = SPI_Transeive('B');
		UART_Transmit(data);
	}
}