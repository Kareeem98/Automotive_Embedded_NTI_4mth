/*
 * calculator.c
 *
 * Created: 2/23/2023 12:10:06 AM
 *  Author: dell
 */ 


#include "calculator.h"

//Keypad keys chars
uint8 keys[] = {	'7', '8', '9', '/',
					'4', '5', '6', '*',
					'1', '2', '3', '-',
					'C', '0', '%', '+'};

uint16 num1 = 0; //first number
uint16 num2 = 0; //second number
uint8 operator = 0; //operator
uint8 result[16]; //result string
uint8 state = equation; //equation state
uint8 input = 0; //input char


uint16 add(uint16 a, uint16 b){
	return (a + b);
}

uint16 subtract(uint16 a, uint16 b){
	return ((int16)(a - b));
}

uint16 multiply(uint16 a, uint16 b){
	return (a * b);
}

uint16 divide(uint16 a, uint16 b){
	return (a / b);
}

uint16 modulus(uint16 a, uint16 b){
	return (a % b);
}

uint8 is_digit(uint8 input){
	if(input >= '0' && input <='9') return 1;
	else return 0;
}

uint8 is_operator(uint8 input){
	if(input == '+' || input =='-' || input =='*' || input =='/' || input =='%') return 1;
	else return 0;
}

uint8 is_equal_key(uint8 input){
	if(input == '=') return 1;
	else return 0;
}

uint8 is_clear_key(uint8 input){
	if(input == 'C') return 1;
	else return 0;
}

void equal_routine(void){	
			LCD_4_bit_sendChar('=');
			state = ready;
}

void calculate_result(void){
	switch(operator){
		case '+':
			sprintf(result, "%d", add(num1, num2));
			break;
			
		case '-':
			sprintf(result, "%d", subtract(num1, num2));
			break;
			
		case '*':
			sprintf(result, "%d", multiply(num1, num2));
			break;
			
		case '/':
			sprintf(result, "%d", divide(num1, num2));
			break;
			
		case '%':
			sprintf(result, "%d", modulus(num1, num2));
			break;
			
		default:
			sprintf(result, "%d", num1);
			break;
	}
}

void calculator_init(void){
	DIO_vWritePin(PORT_D, PIN2, HIGH);
	keypadInit();  //keypad initialization
	LCD_4_bit_init(); //LCD initialization in 4-bit mode
	EXT_INT_Init(); //external interrupt initialization
	external_interrupt_register_callback(equal_routine, NULL, NULL); //setting ISR
	EXT_INT_SET_CONFIG(); //external interrupt enable
}

void calculator_start(void){
	input = keypadGetPressed();
	
	//clearing the screen and reseting numbers to 0
	if(is_clear_key(keys[input])){
		LCD_4_bit_clear();
		num1 = 0;
		num2 = 0;
		operator = 0;
		state = equation;
	}
	
	else if(is_digit(keys[input]) && (state == equation)){
		LCD_4_bit_sendChar(keys[input]);
		
		if(operator==0){
			num1*=10;
			num1+=keys[input];
			num1-='0';
		}
		
		else if(operator!=0){
			num2*=10;
			num2+=keys[input];
			num2-='0';
		}
	}
	
	else if(is_operator(keys[input]) && (state == equation)){
		LCD_4_bit_sendChar(keys[input]);
		operator = keys[input];
	}
	
	if(state == ready){
		calculate_result();
		LCD_4_bit_sendString(result);
		state = done;
	}
}