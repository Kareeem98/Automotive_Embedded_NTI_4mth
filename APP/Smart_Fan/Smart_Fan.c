/*
 * Smart_Fan.c
 *
 * Created: 3/2/2023 2:04:47 AM
 *  Author: dell
 */ 

#include "Smart_Fan.h"

//initialize LCD, Temperature sensor and Motor driver
void Smart_Fan_init(void){
	LCD_4_bit_init();
	LM35_init();
	Motor_B_init();
}

//Smart Fan superloop
void Smart_Fan_Start(void){
	//read the temperature
	uint8 temperature_value = LM35_read();
	
	//fan speed string
	uint8 *fan_speed;
	
	//temperature string
	uint8 temperature[16];
	
	//concatenating the temp value as string with "Temp = " 
	sprintf(temperature, "Temp = %d", temperature_value);
	
	//rotating the motor with speed and frequency based on the temperature
	if(temperature_value < 25){
		fan_speed = "Fan Speed = 0%  "; 
		Motor_B_Rotate(CLOCKWISE, 0, 5000); //speed = 0%
	}
	else if(temperature_value < 30){
		fan_speed = "Fan Speed = 30% ";
		Motor_B_Rotate(CLOCKWISE, 76, 5000);  //speed = 30%, freq = 5KHz
	}
	else if(temperature_value < 35){
		fan_speed = "Fan Speed = 50% ";
		Motor_B_Rotate(CLOCKWISE, 127, 10000); //speed = 50%, freq = 10KHz
	}
	else{
		fan_speed = "Fan Speed = 80% ";
		Motor_B_Rotate(CLOCKWISE, 204, 20000);  //speed = 80%, freq = 20KHz
	}
	
	/***Printing the system state on LCD***/
	LCD_4_bit_firstLine(); //go to first line location 0
	LCD_4_bit_sendString(temperature); //print the temperature string 
	LCD_4_bit_sendString("C  ");  //print the degree symbol
	LCD_4_bit_secondLine(); //go to second line location 0
	LCD_4_bit_sendString(fan_speed); //print fan speed string
}