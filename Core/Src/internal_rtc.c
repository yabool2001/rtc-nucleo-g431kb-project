/*
 * internal_rtc.c
 *
 *  Created on: Sep 15, 2023
 *      Author: sss
 */
#include "internal_rtc.h"

// Declare an external RTC_HandleTypeDef variable named hrtc
extern RTC_HandleTypeDef hrtc;

/*
 * The set_time function is used to set the time and date on a Real-Time Clock (RTC).
 * It takes in seven parameters: hours, minutes, seconds for time and weekday, month, date and year for date.
 * The function first sets up a RTC_TimeTypeDef structure and a RTC_DateTypeDef structure with these parameters.
 * It then calls HAL_RTC_SetTime and HAL_RTC_SetDate to set the time and date on the RTC.
 * If these functions return HAL_OK, it means that the time and date were successfully set.
 * The function also writes a value to a backup register using HAL_RTCEx_BKUPWrite.
 * This could be used for various purposes like checking if the time and date were previously set or not.
 * */
// Define a function named set_time that takes in 7 parameters: Hours, Minutes, Seconds, WeekDay, Month, Date, Year
void set_time (uint8_t Hours, uint8_t Minutes, uint32_t Seconds, uint8_t WeekDay, uint8_t Month, uint8_t Date, uint8_t Year)
{
  // Declare a RTC_TimeTypeDef variable named sTime
  RTC_TimeTypeDef sTime;
  // Declare a RTC_DateTypeDef variable named sDate
  RTC_DateTypeDef sDate;

  // Set the Hours field of sTime to the Hours parameter
  sTime.Hours = Hours;
  // Set the Minutes field of sTime to the Minutes parameter
  sTime.Minutes = Minutes;
  // Set the Seconds field of sTime to the Seconds parameter
  sTime.Seconds = Seconds;
  // Set the DayLightSaving field of sTime to RTC_DAYLIGHTSAVING_NONE
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  // Set the StoreOperation field of sTime to RTC_STOREOPERATION_RESET
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;

  // Call HAL_RTC_SetTime with parameters hrtc, &sTime and RTC_FORMAT_BCD. If it returns anything other than HAL_OK, do nothing.
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
  }

  // Set the WeekDay field of sDate to the WeekDay parameter
  sDate.WeekDay = WeekDay;
  // Set the Month field of sDate to the Month parameter
  sDate.Month = Month;
  // Set the Date field of sDate to the Date parameter
  sDate.Date = Date;
  // Set the Year field of sDate to the Year parameter
  sDate.Year = Year;

  // Call HAL_RTC_SetDate with parameters hrtc, &sDate and RTC_FORMAT_BCD. If it returns anything other than HAL_OK, do nothing.
  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
  }

  // Call HAL_RTCEx_BKUPWrite with parameters hrtc, RTC_BKP_DR1 and dumy value like 0x32F2
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2);
}

/*
 * The get_time function is used to get the current time and date from a Real-Time Clock (RTC).
 * It first calls HAL_RTC_GetTime and HAL_RTC_GetDate to get the current time and date.
 * It then formats these values into strings using sprintf and stores them in ctime and cdate.
 * The time is formatted as “HH:MM:SS” and the date as “DD-MM-YYYY”.
 * Finally, it prints these strings to the console.
 * This function is useful when you want to display the current time and date in a human-readable format.
 * */
// Define a function named get_time that takes no parameters
void get_time(void)
{
 // Declare a RTC_DateTypeDef variable named gDate
 RTC_DateTypeDef gDate;
 // Declare a RTC_TimeTypeDef variable named gTime
 RTC_TimeTypeDef gTime;

 // Allocate space for "HH:MM:SS\0"
 char ctime[9];
 // Allocate space for "DD-MM-YYYY\0"
 char cdate[11];

/* Get the RTC current Time */
 // Call HAL_RTC_GetTime with parameters hrtc, &gTime and RTC_FORMAT_BIN
 HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
/* Get the RTC current Date */
 // Call HAL_RTC_GetDate with parameters hrtc, &gDate and RTC_FORMAT_BIN
 HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
/* Display time Format: hh:mm:ss */
 // Use sprintf to format the time into ctime
 sprintf(ctime,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);
/* Display date Format: dd-mm-yy */
 // Use sprintf to format the date into cdate
 sprintf(cdate,"%02d-%02d-%4d",gDate.Date, gDate.Month, 2000 + gDate.Year);

 // Print the time
 printf("%s\r\n", ctime);
 // Print the date
 printf("%s\r\n", cdate);
}

/*
 * The set_alarm function is used to set an alarm on a Real-Time Clock (RTC).
 * It takes in four parameters: hours, minutes, seconds for time and date for date.
 * The function first sets up a RTC_AlarmTypeDef structure with these parameters.
 * It then calls HAL_RTC_SetAlarm_IT to set the alarm on the RTC.
 * If this function returns HAL_OK, it means that the alarm was successfully set.
 * This function is useful when you want to set an alarm at a specific time and date.
 * */
// Define a function named set_alarm that takes in 4 parameters: Hours, Minutes, Seconds, Date
void set_alarm (uint8_t Hours, uint8_t Minutes, uint32_t Seconds, uint8_t Date)
{
  // Declare a RTC_AlarmTypeDef variable named sAlarm
  RTC_AlarmTypeDef sAlarm;

  // Set the Hours field of AlarmTime in sAlarm to the Hours parameter
  sAlarm.AlarmTime.Hours = Hours;
  // Set the Minutes field of AlarmTime in sAlarm to the Minutes parameter
  sAlarm.AlarmTime.Minutes = Minutes;
  // Set the Seconds field of AlarmTime in sAlarm to the Seconds parameter
  sAlarm.AlarmTime.Seconds = Seconds;
  // Set the SubSeconds field of AlarmTime in sAlarm to 0x00
  sAlarm.AlarmTime.SubSeconds = 0x00;
  // Set the DayLightSaving field of AlarmTime in sAlarm to RTC_DAYLIGHTSAVING_NONE
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  // Set the StoreOperation field of AlarmTime in sAlarm to RTC_STOREOPERATION_RESET
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  // Set the AlarmMask field of sAlarm to RTC_ALARMMASK_NONE
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  // Set the AlarmSubSecondMask field of sAlarm to RTC_ALARMSUBSECONDMASK_ALL
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  // Set the AlarmDateWeekDaySel field of sAlarm to RTC_ALARMDATEWEEKDAYSEL_DATE
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  // Set the AlarmDateWeekDay field of sAlarm to the Date parameter
  sAlarm.AlarmDateWeekDay = Date;
  // Set the Alarm field of sAlarm to RTC_ALARM_A
  sAlarm.Alarm = RTC_ALARM_A;

  // Call HAL_RTC_SetAlarm_IT with parameters hrtc, &sAlarm and RTC_FORMAT_BCD. If it returns anything other than HAL_OK, do nothing.
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
  }
}

/*
 * The HAL_RTC_AlarmAEventCallback function is a callback function that gets called when an Alarm A interrupt occurs in the Real-Time Clock (RTC).
 * It takes in a pointer to a RTC_HandleTypeDef variable.
 * When an Alarm A interrupt occurs, this function is automatically called, and it prints “Alarm Interrupt Occurred” to the console.
 * This function is useful for providing a notification or performing a specific action when an alarm goes off.
 */
// Define a function named HAL_RTC_AlarmAEventCallback that takes in a pointer to a RTC_HandleTypeDef variable named hrtc
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  // Print "Alarm Interrupt Occurred" to the console
  printf("Alarm Interrupt Occurred\r\n");
}

