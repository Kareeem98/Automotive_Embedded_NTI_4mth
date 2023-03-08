/*
 * SPI_Reg.h
 *
 * Created: 3/4/2023 12:16:01 PM
 *  Author: kareem
 */ 
#ifndef SPI_REG_H_
#define SPI_REG_H_

#include "../../LIB/Datatypes.h"



//	SPI Registers

#define SPCR	(*(volatile uint8*)(0x2D))
#define SPSR	(*(volatile uint8*)(0x2E))
#define SPDR	(*(volatile uint8*)(0x2F))
#define SREG	(*(volatile uint8*)(0x5F))			//FOR Global interrupt
#define DDRB	(*(volatile uint8*)(0x37))
#define PORTB	(*(volatile uint8*)(0x38))

//global interrupt enable bin
#define GIE 7


// Spcr reg pins
#define SPIE 7
#define SPE	 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

// spsr reg pins

#define SPIF  7
#define WCOL  6
#define SPI2X 0

// spdr reg pins

//#define MSB  7
//#define LSB  0


#endif /* SPI_REG_H_ */