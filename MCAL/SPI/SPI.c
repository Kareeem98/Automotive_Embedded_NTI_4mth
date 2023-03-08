/*
 * SPI.c
 *
 * Created: 3/4/2023 12:17:06 PM
 *  Author: dell
 */ 

#include "SPI_Interface.h"
#include "SPI_Reg.h"
#include "../../LIB/Calcbit.h"

void SPI_init(void){
#if SPI_MODE == MASTER
	//set pins directions
	setbit(DDRB,MOSI);
	setbit(DDRB,SCK);
	setbit(DDRB,SS);
	clearbit(DDRB,MISO);
	
	//write high to SS
	setbit(PORTB,SS);
	
	setbit(SPCR,SPE); //enable SPI
	
	//set interrupt configs
	if(SPI_INT == SP_EN) setbit(SPCR,SPIE);
	else if(SPI_INT == SP_DIS) clearbit(SPCR,SPIE);
	
	//set data order configs
	if(DATA_ORDER == MSB_FIRST) clearbit(SPCR,DORD);
	else if(DATA_ORDER == LSB_FIRST) setbit(SPCR,DORD);
	
	//set phase and polarity configs
	clearbit(SPCR,CPOL);
	clearbit(SPCR,CPHA);
	
	switch(PRESCALER){
		case 2:
			clearbit(SPCR,SPR0);
			clearbit(SPCR,SPR1);
			setbit(SPSR,SPI2X);
			break;
			
			case 4:
			clearbit(SPCR,SPR0);
			clearbit(SPCR,SPR1);
			clearbit(SPSR,SPI2X);
			break;
			
			case 8:
			setbit(SPCR,SPR0);
			clearbit(SPCR,SPR1);
			setbit(SPSR,SPI2X);
			break;
			
			case 16:
			setbit(SPCR,SPR0);
			clearbit(SPCR,SPR1);
			clearbit(SPSR,SPI2X);
			break;
			
			case 32:
			clearbit(SPCR,SPR0);
			setbit(SPCR,SPR1);
			setbit(SPSR,SPI2X);
			break;
			
			case 64:
			clearbit(SPCR,SPR0);
			setbit(SPCR,SPR1);
			clearbit(SPSR,SPI2X);
			break;
			
			case 128:
			setbit(SPCR,SPR0);
			setbit(SPCR,SPR1);
			clearbit(SPSR,SPI2X);
			break;
		}
		
		setbit(SPCR,MSTR);//enable as master
		#endif

		#if SPI_MODE == SLAVE
		//set pins directions
		clearbit(DDRB,MOSI);
		clearbit(DDRB,SCK);
		clearbit(DDRB,SS);
		setbit(DDRB,MISO);

		//enable SPI
		setbit(SPCR,SPE);

		//set interrupt configs
		if(SPI_INT == SP_EN) setbit(SPCR,SPIE);
		else if(SPI_INT == SP_DIS) clearbit(SPCR,SPIE);

		//set data order configs
		if(DATA_ORDER == MSB_FIRST) clearbit(SPCR,DORD);
		else if(DATA_ORDER == LSB_FIRST) setbit(SPCR,DORD);

		//set phase and polarity configs
		clearbit(SPCR,CPOL);
		clearbit(SPCR,CPHA);

		clearbit(SPCR,MSTR);//enable as slave
		#endif
	}

	uint8 SPI_Transeive(uint8 data){
		#if SPI_MODE == MASTER
		clearbit(PORTB,SS);
		SPDR = data;
		while(getbit(SPSR,SPIF)==0);
		setbit(PORTB,SS);
		return SPDR;
		#endif

		#if SPI_MODE == SLAVE
		SPDR = data;
		while(getbit(SPSR,SPIF)==0);
		setbit(PORTB,SS);
		#endif
	}