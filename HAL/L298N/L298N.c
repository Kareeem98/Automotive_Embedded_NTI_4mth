/*
 * L298N.c
 *
 * Created: 3/2/2023 1:39:58 AM
 *  Author: dell
 */ 

#include "L298N.h"

void Motor_A_init(){
	//set direction pins to output
	DIO_vSetPinDirection(IN1, OUT);
	DIO_vSetPinDirection(IN2, OUT);
	
	//initialize PWM
	PWM_Init();
}

void Motor_A_Rotate(uint8 direction, uint8 speed, uint32 freq){
	//set motor direction to anti-clockwise
	if (direction == ANTI_CLOCKWISE){
		DIO_vWritePin(IN1, HIGH);
		DIO_vWritePin(IN2, LOW);
	}
	
	//set motor direction to clockwise
	else if (direction == CLOCKWISE){
		DIO_vWritePin(IN1, LOW);
		DIO_vWritePin(IN2, HIGH);
	}
	
	//generate PWM on channel A
	PWM_Generate_CHANNELA(speed, freq);
}

void Motor_B_init(){
	//set direction pins to output
	DIO_vSetPinDirection(IN3, OUT);
	DIO_vSetPinDirection(IN4, OUT);
	
	//initialize PWM
	PWM_Init();
}

void Motor_B_Rotate(uint8 direction, uint8 speed, uint32 freq){
	//set motor direction to anti-clockwise
	if (direction == ANTI_CLOCKWISE){
		DIO_vWritePin(IN3, HIGH);
		DIO_vWritePin(IN4, LOW);
	}
	
	//set motor direction to clockwise
	else if (direction == CLOCKWISE){
		DIO_vWritePin(IN3, LOW);
		DIO_vWritePin(IN4, HIGH);
	}
	
	//generate PWM on channel B
	PWM_Generate_CHANNELB(speed, freq);
}