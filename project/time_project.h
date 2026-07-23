#ifndef TIME_PROJECT_H
#define TIME_PROJECT_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

typedef struct Date{
	int year,month,day;
}Date;

// relate to the date
Date getTodayDate(void);//get current system date and use time.h function from hint
Date getOffsetDate(Date d, int offset);
//relate to the time
void getCurrentTime(int* hour, int* minute);
bool whetherTimePassed(int timeSlot);
int firstAvailableTimeSlot(void);//the first time slot that you can apply today
void transferDateFormat(Date d, char *dateFormat);//change the format of time xxxx.xx.xx
const char* chooseTimeSlot(int index);
bool is_today(Date date);

#endif  //


