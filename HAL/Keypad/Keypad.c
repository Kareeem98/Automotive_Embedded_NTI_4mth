/*
 * Keypad.c
 *
 * Created: 2/19/2023 10:30:12 AM
 *  Author: dell
 */ 


#include "Keypad.h"

void keypadInit(){
	for(uint8 i=0; i<numberOfRows; i++){
		//set rows pins to output
		DIO_vSetPinDirection(rowsPort, rows[i], OUT);
		//write high on rows
		DIO_vWritePin(rowsPort, rows[i], HIGH);
	}
	
	for(uint8 i=0; i<numberOfColns; i++){
		//set columns pins to input with pull-up
		DIO_vSetPinDirection(colnsPort, colns[i], IN_PULLUP);
	}
}

uint8 keypadGetPressed(){
	for(uint8 i=0; i<numberOfRows; i++){
		DIO_vWritePin(rowsPort, rows[i], LOW);
		
		for (uint8 j=0; j<numberOfColns; j++){
			
			if(DIO_u8GetPinValue(colnsPort, colns[j]) == LOW){
				//Debouncing Handler
				uint8 counter = 0;
				for(uint8 k=0; k<8; k++){
					if(DIO_u8GetPinValue(colnsPort, colns[j]) == 0) counter++;
					else if(DIO_u8GetPinValue(colnsPort, colns[j]) == 1) counter=0;
					TIMER0_DelayMilliSeconds_with_Blocking(debounce_delay);
				}
				
				if(counter>=4){
					while(DIO_u8GetPinValue(colnsPort, colns[j]) == LOW);
					return (numberOfColns*i + j);
				}
			}
			
		}
		
		DIO_vWritePin(rowsPort, rows[i], HIGH);

	}
	return notPressed;
}
