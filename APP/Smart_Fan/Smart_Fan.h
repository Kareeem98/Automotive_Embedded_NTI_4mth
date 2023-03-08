/*
 * Smart_Fan.h
 *
 * Created: 3/2/2023 2:04:32 AM
 *  Author: dell
 */ 


#ifndef SMART_FAN_H_
#define SMART_FAN_H_

#include "../../HAL/LCD/LCD.h"
#include "../../HAL/L298N/L298N.h"
#include "../../HAL/LM35/LM35.h"

void Smart_Fan_init(void);
void Smart_Fan_Start(void);


#endif /* SMART_FAN_H_ */