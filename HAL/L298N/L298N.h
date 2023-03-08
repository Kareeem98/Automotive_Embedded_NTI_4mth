/*
 * L298N.h
 *
 * Created: 3/2/2023 1:39:44 AM
 *  Author: dell
 */ 


#ifndef L298N_H_
#define L298N_H_

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/PWM/PWM_Interface.h"

//Motor A direction pins
#define IN1 PORT_C, PIN4
#define IN2 PORT_C, PIN5
//Motor A Speed pin
#define EN1 CHANNEL_A_PIN

//Motor B direction pins
#define IN3 PORT_C, PIN6
#define IN4 PORT_C, PIN7
//Motor B Speed pin
#define EN2 CHANNEL_B_PIN

//Motor directions
#define CLOCKWISE (0)
#define ANTI_CLOCKWISE (1)

//L293N APIs
void Motor_A_init(); //initialize motor A
void Motor_A_Rotate(uint8 direction, uint8 speed, uint32 freq); //start motor A motion

void Motor_B_init(); //initialize motor B
void Motor_B_Rotate(uint8 direction, uint8 speed, uint32 freq); //start motor B motion


#endif /* L298N_H_ */