/*
 * Timer0.c
 *
 * Created: 2/24/2023 1:35:06 PM
 *  Author: dell
 */ 

#include "Timer0_Interface.h"


//sets Tmer0 configs (Mode, interrupt)


//Generic Function(Not used)
/*
 void TIMER0_DelayMilliSeconds_with_Blocking(uint16 Milli_Seconds){
	if(Config.Mode == NORMAL_MODE){
		uint32 overflowCounter = 0;
		
		double tickTime = ((double)(Config.Presclar) * 1000)/F_CPU;
		
		uint32 numberOfOverflows = (Milli_Seconds/(256*tickTime));
		if((Milli_Seconds/(256*tickTime)) > numberOfOverflows) numberOfOverflows++;
		
	
		uint8 initialValue = 256 - (Milli_Seconds/(tickTime*numberOfOverflows));
		
		TCNT0 = initialValue;
		TIMER0_Start();
		while(overflowCounter < numberOfOverflows){
			while(getbit(TIFR,TIFR_TOV0) == 0);
			TCNT0 = initialValue;
			setbit(TIFR,TIFR_TOV0);
			overflowCounter++;
		}
		overflowCounter=0;
		TIMER0_Stop();
	}
	
	else if(Config.Mode == CTC_MODE){
		uint32 compareMatcheCounter = 0;
		
		double tickTime = ((double)(Config.Presclar) * 1000)/F_CPU;
		
		uint32 numberOfCompareMatches = (Milli_Seconds/(256*tickTime));
		if((Milli_Seconds/(256*tickTime)) > numberOfCompareMatches) numberOfCompareMatches++;
		
		
		uint8 compareValue = (Milli_Seconds/(tickTime*numberOfCompareMatches));
		
		OCR0 = compareValue;
		TIMER0_Start();
		while(compareMatcheCounter < numberOfCompareMatches){
			while(getbit(TIFR,TIFR_OCF0) == 0);
			setbit(TIFR,TIFR_OCF0);
			compareMatcheCounter++;
		}
		compareMatcheCounter=0;
		TIMER0_Stop();
	}
 }*/