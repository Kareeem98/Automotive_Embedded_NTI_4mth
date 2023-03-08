/*
 * Debouncing.h
 *
 * Created: 2/17/2023 11:34:17 PM
 *  Author: dell
 */ 


#ifndef DEBOUNCING_H_
#define DEBOUNCING_H_


#include "../../LIB/Calcbit.h"
#include "../../LIB/Datatypes.h"

#define delay_time 2

#define HIGH 1
#define LOW 0

uint8 Debounce_Check(uint8 Input_Signal);


#endif /* DEBOUNCING_H_ */