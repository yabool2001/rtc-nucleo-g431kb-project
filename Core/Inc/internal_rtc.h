/*
 * internal_rtc.h
 *
 *  Created on: Sep 15, 2023
 *      Author: sss
 */

#ifndef INC_INTERNAL_RTC_H_
#define INC_INTERNAL_RTC_H_

#include "main.h"
#include<stdio.h>

void set_time (uint8_t Hours, uint8_t Minutes, uint32_t Seconds, uint8_t WeekDay, uint8_t Month, uint8_t Date, uint8_t Year);
void get_time(void);
void set_alarm (uint8_t Hours, uint8_t Minutes, uint32_t Seconds, uint8_t Date);

#endif /* INC_INTERNAL_RTC_H_ */
