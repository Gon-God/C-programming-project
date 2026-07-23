#include "time_project.h"
//helper function in this file
static int dayInThisMonth(Date d){
	int a[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (d.month == 2 && (d.year%4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0)){
		return 29;}
	else return a[d.month-1];
}
// relate to the date

//get current system date and use time.h function from hint
Date getTodayDate(void){
	Date today;
	time_t now;
	struct tm* tblock;
	//the information from hint
    time(&now);                 
    tblock = localtime(&now);   
    today.year = tblock->tm_year + 1900;
    today.month = tblock->tm_mon + 1;
    today.day = tblock->tm_mday;
    return today;
}

Date getOffsetDate(Date d, int offset){
	int i,max;
	Date result = d;
	max = dayInThisMonth(result);
	for (i=0;i<offset;i++){
		result.day++;
		if (result.day>max){
			result.day=1;
			result.month++;
			if (result.month>12){
				result.year+=1;
				result.month=1;
			}}}
	return result;
}

//relate to the time
void getCurrentTime(int* hour, int* minute){
	time_t now;
	struct tm* tblock;
	time(&now);
	tblock = localtime(&now);
	*hour = tblock->tm_hour;
	*minute = tblock->tm_min;
}
/* Definition of time slots (based on end time):
 * Index 0: 9:00每9:50, ends at 9:50
 * Index 1: 10:00每10:50, ends at 10:50
 * Index 2: 11:00每11:50, ends at 11:50
 * Index 3: 12:00每12:50, ends at 12:50
 * Index 4: 13:00每13:50, ends at 13:50
 * Index 5: 14:00每14:50, ends at 14:50
 * Index 6: 15:00每15:50, ends at 15:50
 * Index 7: 16:00每16:50, ends at 16:50
 */
bool whetherTimePassed(int timeSlot){
	int hour,minute;
	getCurrentTime(&hour,&minute);
	int hourAllowed[]={9,10,11,12,13,14,15,16};
	if (timeSlot <0||timeSlot>7){
		return true;}
	if (hour>=hourAllowed[timeSlot]){
		return true;}
	return false;
}/* Rule: Once the current time reaches any full hour, 
users cannot book either the time slot of that hour,
 nor any preceding time slots. */
//the first time slot that you can apply today
int firstAvailableTimeSlot(void){
	int i;
	for (i=0;i<8;i++){
		if (!whetherTimePassed(i)){
			return i;}}
	return -1;
}
//change the format of time xxxx.xx.xx
void transferDateFormat(Date d, char *dateFormat){
				sprintf(dateFormat,"%d.%d.%d",d.year,d.month,d.day);
			}

const char* chooseTimeSlot(int index){
	static const char* timeslots[] = {
		"9:00 am 每 9:50 am",
		"10:00 am 每 10:50 am",
        "11:00 am 每 11:50 am",
        "12:00 pm 每 12:50 pm",
        "13:00 pm 每 13:50 pm",
        "14:00 pm 每 14:50 pm",
        "15:00 pm 每 15:50 pm",
        "16:00 pm 每 16:50 pm"};
	if (index < 0|| index>7){
		return NULL;}
	return timeslots[index];
}
bool is_today(Date date){
 Date today = getTodayDate();
    return (date.year == today.year && date.month == today.month && date.day == today.day);
}

