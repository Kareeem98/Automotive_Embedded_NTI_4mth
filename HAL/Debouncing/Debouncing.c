/*
 * Debouncing.c
 *
 * Created: 2/17/2023 11:34:31 PM
 *  Author: dell
 */ 
#include "Debouncing.h"


uint8 Debounce_Check(uint8 Input_Signal){
	uint8 counter=0;
	for(uint8 k=0; k<8; k++){
		if(Input_Signal == 0)
		counter++;
		
		else if(Input_Signal == 1)
		counter=0;
		
		_delay_ms(delay_time);
	}
	
	if(counter >= 4) return 1;
	else return 0;
}