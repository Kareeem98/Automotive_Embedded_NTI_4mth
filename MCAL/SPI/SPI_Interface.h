/*
 * SPI_Interface.h
 *
 * Created: 3/4/2023 12:16:51 PM
 *  Author: Kareem
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "../../LIB/Datatypes.h"

// SPI COnfg

#define SPI_MODE SLAVE
#define SPI_INT	SP_DIS
#define	DATA_ORDER LSB_FIRST
#define PRESCALER   128


#define SLAVE  0
#define MASTER 1 
 
#define SCK  7
#define MISO 6
#define MOSI 5
#define SS	 4

#define SP_DIS  0
#define	SP_EN   1
 
#define MSB_FIRST 0
#define LSB_FIRST 1
 
 
 
 
void SPI_init(void);
uint8 SPI_Transeive(uint8 data);









#endif /* SPI_INTERFACE_H_ */