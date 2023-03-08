/*
 * UART.c
 *
 * Created: 3/3/2023 12:00:22 PM
 *  Author: dell
 */ 
#include "UART_Interface.h"
#include "UART_Reg.h"
#include "../../LIB/Calcbit.h"
#include "../DIO/DIO_Interface.h"

static uint16 *UART_RX_INT_Buffer;

uint8 is_normalMode(uint32 BaudRate){
	float32 temp_UBRR = ((float32)F_CPU/(16*BaudRate))-1;
	if((temp_UBRR - (uint16)temp_UBRR)>=0.5) temp_UBRR++;
	
	float32 temp_Baud = (F_CPU/(16*((uint16)temp_UBRR+1)));
	float32 error = (temp_Baud/BaudRate) -1;
	
	if((error <= 0.01) && (error >= -0.01)) return 1;
	else return 0;
}


void UART_init (uint32 BaudRate){
	uint16 UBBR_value;
	uint8 UCSRC_value;
	if(is_normalMode(BaudRate)){
		clearbit(UCSRA,U2X); //disable double speed mode (normal mode)
		UBBR_value = ((float32)F_CPU/(16*BaudRate))-1;
	}
	else{
		setbit(UCSRA,U2X); //enable double speed mode
		UBBR_value = ((float32)F_CPU/(8*BaudRate))-1;
	}
	
	//assign baud rate UBBR value to UBBR register
	UBRRH = (UBBR_value>>8);
	UBRRL = UBBR_value;
	
	//enable or disable RX interrupt
	if(UARTConfig.RX_INT == U_EN){
		setbit(SREG,GIE);
		setbit(UCSRB,RXCIE);
	}
	else if(UARTConfig.RX_INT == U_DIS) clearbit(UCSRB,RXCIE);
	
	//enable or disable TX interrupt
	if(UARTConfig.TX_INT == U_EN){
		setbit(SREG,GIE);
		setbit(UCSRB,TXCIE);
	}
	else if(UARTConfig.TX_INT == U_DIS) clearbit(UCSRB,TXCIE);
	
	//enable or disable data register empty interrupt
	if(UARTConfig.UDR_INT == U_EN){
		setbit(SREG,GIE);
		setbit(UCSRB,UDRIE);
	}
	else if(UARTConfig.UDR_INT == U_DIS) clearbit(UCSRB,UDRIE);
	
	
	setbit(UCSRC_value,URSEL); //to access UCSRC register instead of UBBR register
	clearbit(UCSRC_value,UMSEL); //set to Asynchronous
	
	//set parity mode
	switch(UARTConfig.Parity_Mode){
		case DIS_PARITY:
			clearbit(UCSRC_value,UPM0);
			clearbit(UCSRC_value,UPM1);
			break;
			
		case EVEN_PARITY:
			clearbit(UCSRC_value,UPM0);
			setbit(UCSRC_value,UPM1);
			break;
			
		case ODD_PARITY:
			setbit(UCSRC_value,UPM0);
			setbit(UCSRC_value,UPM1);
			break;
	}
	
	//set stop bit mode
	if(UARTConfig.Stop_Bit == ONE_BIT) clearbit(UCSRC_value,USBS);
	else if(UARTConfig.Stop_Bit == TWO_BITS) setbit(UCSRC_value,USBS);
	
	
	//set character size
	switch(UARTConfig.CHAR_SIZE){
		case SIZE_5:
			clearbit(UCSRC_value,UCSZ0);
			clearbit(UCSRC_value,UCSZ1);
			clearbit(UCSRB,UCSZ2);
			break;
			
		case SIZE_6:
			setbit(UCSRC_value,UCSZ0);
			clearbit(UCSRC_value,UCSZ1);
			clearbit(UCSRB,UCSZ2);
			break;
			
		case SIZE_7:
			clearbit(UCSRC_value,UCSZ0);
			setbit(UCSRC_value,UCSZ1);
			clearbit(UCSRB,UCSZ2);
			break;
			
		case SIZE_8:
			setbit(UCSRC_value,UCSZ0);
			setbit(UCSRC_value,UCSZ1);
			clearbit(UCSRB,UCSZ2);
			break;
			
		case SIZE_9:
			setbit(UCSRC_value,UCSZ0);
			setbit(UCSRC_value,UCSZ1);
			setbit(UCSRB,UCSZ2);
			break;	
	}
	
	//Enable TX and RX
	setbit(UCSRB,TXEN);
	setbit(UCSRB,RXEN);
	UCSRC = UCSRC_value;
}


void UART_Transmit(uint16 data){
	while(getbit(UCSRA,UDRE) == 0);
	if(UARTConfig.CHAR_SIZE == SIZE_9){
		if(getbit(data,8) == 0) clearbit(UCSRB,TXB8);
		else if(getbit(data,8) == 1) setbit(UCSRB,TXB8);	
	}
	UDR = data;
}


uint16 UART_Recieve(void){
	while(getbit(UCSRA,RXC) == 0);
	if(UARTConfig.CHAR_SIZE == SIZE_9){
		return ((getbit(UCSRB,RXB8)<<8) | UDR);
	}
	else return UDR;
}

void UART_Set_Receive_Buffer(uint16 *RX_Buffer){
	UART_RX_INT_Buffer = RX_Buffer;
}


ISR(UART_RX_INT){
	/*if(UARTConfig.CHAR_SIZE == SIZE_9){
		*UART_RX_INT_Buffer = ((getbit(UCSRB,RXB8)<<8) | UDR);
	}
	else *UART_RX_INT_Buffer = UDR;*/
	DIO_vTogglePin(PORT_C,PIN5);
}