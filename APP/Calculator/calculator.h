/*
 * calculator.h
 *
 * Created: 2/23/2023 12:09:50 AM
 *  Author: dell
 */ 


#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "../../MCAL/EXTI/External_INT_Interface.h"
#include "../../HAL/Keypad/Keypad.h"
#include "../../HAL/LCD/LCD.h"

//states of the calculation
#define equation 0
#define ready 1
#define done 2

//Calculator APIs
uint16 add(uint16 a, uint16 b); //a + b
uint16 subtract(uint16 a, uint16 b); //a - b
uint16 multiply(uint16 a, uint16 b); //a * b
uint16 divide(uint16 a, uint16 b); //a / b
uint16 modulus(uint16 a, uint16 b); //a % b
uint8 is_digit(uint8 input);  //returns True if input is (0 to 9)
uint8 is_operator(uint8 input);  //returns True if input is operator (+, -, *, /, %)
uint8 is_equal_key(uint8 input);  //returns True if input is '='
uint8 is_clear_key(uint8 input);  //returns True if clear button is pressed
void equal_routine(void);  //ISR when '=' is pressed
void calculate_result(void);  //calculates the result
void calculator_init(void); //app initialization
void calculator_start(void); //app main function


#endif /* CALCULATOR_H_ */