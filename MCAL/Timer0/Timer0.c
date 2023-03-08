/*
 * Timer0.c
 *
 * Created: 2/24/2023 1:35:06 PM
 *  Author: dell
 */ 

#include "Timer0_Interface.h"


//sets Tmer0 configs (Mode, interrupt)void TIMER0_SetConfig(void){	switch(timerConfig.Mode){		case NORMAL_MODE:			clearbit(TCCR0,TCCR0_WGM01);			clearbit(TCCR0,TCCR0_WGM00);						if(timerConfig.Enable_Interrupt == TIMER0_INT_ENABLE) setbit(TIMSK,TIMSK_TOIE0);			else clearbit(TIMSK,TIMSK_TOIE0);						break;					case PWM_PHASE_CORRECT:			clearbit(TCCR0,TCCR0_WGM01);			setbit(TCCR0,TCCR0_WGM00);			break;					case CTC_MODE:			setbit(TCCR0,TCCR0_WGM01);			clearbit(TCCR0,TCCR0_WGM00);			clearbit(TCCR0,TCCR0_COM00);			clearbit(TCCR0,TCCR0_COM01);									if(timerConfig.Enable_Interrupt == TIMER0_INT_ENABLE) setbit(TIMSK,TIMSK_OCIE0);			else clearbit(TIMSK,TIMSK_OCIE0);						break;		case FAST_PWM:			setbit(TCCR0,TCCR0_WGM01);			setbit(TCCR0,TCCR0_WGM00);			break;	}} //delay in milliseconds with blocking the cpu (busy wait)//if prescaler is 64 and Fcpu is 16MHz.. ticktime will be 4us..so we need 250 ticks to form 1ms//we need each timer cycle (overflow or compare match) to form 1ms.. then each cycle should be 250 ticks//number of milliseconds to be delayed is the number of cycles we need to perform void TIMER0_DelayMilliSeconds_with_Blocking(uint16 Milli_Seconds){		//for normal mode we load TCNT register with initial value 5 so each overflow is 250 ticks	if(timerConfig.Mode == NORMAL_MODE){		TCNT0 = 5;  //load TCNT with initial value		TCCR0 = (TCCR0 & PRESCALER_CLEAR) | PRESCALER_64;  //start timer with prescaler 64		while(Milli_Seconds > 0){			while(getbit(TIFR,TIFR_TOV0) == 0);			TCNT0 = 5;   //reload TCNT with initial value			setbit(TIFR,TIFR_TOV0);  //clear overflow flag			Milli_Seconds--;		}		TCCR0 &= PRESCALER_CLEAR;   //stop timer	}		//for CTC mode we load OCR register with 250 so each compare match is 250 ticks	else if(timerConfig.Mode == CTC_MODE){		OCR0 = 250;  //load OCR with compare match value		TCCR0 = (TCCR0 & PRESCALER_CLEAR) | PRESCALER_64;  //start timer with prescaler 64		while(Milli_Seconds > 0){			while(getbit(TIFR,TIFR_OCF0) == 0); //busy wait for compare match flag			setbit(TIFR,TIFR_OCF0); //clear compare match flag			Milli_Seconds--;		}		TCCR0 &= PRESCALER_CLEAR;   //stop timer	}}//delay in microseconds with blocking the cpu (busy wait)//if prescaler is 1 (no prescaler) and Fcpu is 16MHz.. ticktime will be 1/16us..so we need 16 ticks to form 1us//we need each timer cycle (overflow or compare match) to form 1us.. then each cycle should be 16 ticks//number of microseconds to be delayed is the number of cycles we need to performvoid TIMER0_DelayMicroSeconds_with_Blocking(uint16 Micro_Seconds){	//for normal mode we load TCNT register with initial value 239 so each overflow is 16 ticks	if(timerConfig.Mode == NORMAL_MODE){		TCNT0 = 239;  //load TCNT with initial value		TCCR0 = (TCCR0 & PRESCALER_CLEAR) | PRESCALER_1; //start timer with no prescaler		while(Micro_Seconds > 0){			while(getbit(TIFR,TIFR_TOV0) == 0); //busy wait for overflow flag			TCNT0 = 239;  //reload TCNT with initial value			setbit(TIFR,TIFR_TOV0); //clear overflow flag			Micro_Seconds--;		}		TCCR0 &= PRESCALER_CLEAR;  //stop timer	}		//for CTC mode we load OCR register with 16 so each compare match is 16 ticks	else if(timerConfig.Mode == CTC_MODE){		OCR0 = 16;  //load OCR with compare match value		TCCR0 = (TCCR0 & PRESCALER_CLEAR) | PRESCALER_1; //start timer with no prescaler		while(Micro_Seconds > 0){			while(getbit(TIFR,TIFR_OCF0) == 0); //busy wait for compare match flag			setbit(TIFR,TIFR_OCF0); //clear compare match flag			Micro_Seconds--;		}		TCCR0 &= PRESCALER_CLEAR; //stop timer	}}


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