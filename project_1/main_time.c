

#include <stdio.h>
#include "time_project.h"


int main_time(int argc, char *argv[])
{
    printf("       time tool module test\n");
	printf("============================================================\n");
	printf(" [test 1] get the current date\n");
	printf("------------------------------------------------------------\n");
	Date today = getTodayDate();
	printf("   current date: %d Äê %d ÔÂ %d ÈÕ\n",today.year,today.month,today.day);
	printf("\n");

	printf(" [test 2] transfer date format \n");
	printf("------------------------------------------------------------\n");
	char dateFormat[22];
	transferDateFormat(today, dateFormat);
	printf("  date format(xxxx.xx.xx)£º%s\n", dateFormat);
	printf("\n");

	printf(" [test 3]  calculate offset date\n");
	printf("------------------------------------------------------------\n");
	Date day2 = getOffsetDate(today, 1);//tomorrow date
	Date day3 = getOffsetDate(today, 2);//dayafter date
	char d2[22],d3[22];
	transferDateFormat(day2, d2);
	transferDateFormat(day3, d3);
	printf("  tomorrow:%s\n",d2);
	printf("  day after:%s\n",d3);
	printf("\n");

	printf(" [test 4] Cross-month / cross-year test\n");
	printf("use to test the function");
	printf("------------------------------------------------------------\n");
    Date testDate1 = {2026, 12, 30};
    Date result1 = getOffsetDate(testDate1, 2);
    printf("  2026.12.30 + 2day = %d.%d.%d\n",result1.year, result1.month, result1.day);
    Date testDate2 = {2026, 12, 31};
    Date result2 = getOffsetDate(testDate2, 1);
    printf("  2026.12.31 + 1day = %d.%d.%d\n",result2.year, result2.month, result2.day);
    Date testDate3 = {2024, 2, 28};
    Date result3 = getOffsetDate(testDate3, 1);
    printf("  2024.02.28 + 1day = %d.%d.%d\n",result3.year, result3.month, result3.day);
    printf("\n");

	printf(" [test 5] get current time\n");
	printf("------------------------------------------------------------\n");
	int hour, minute;
	getCurrentTime(&hour,&minute);
	printf("  current time;%02d:%02d\n", hour, minute);
	printf("\n");

	printf(" [test 6] timeslot list\n");
	printf("------------------------------------------------------------\n");
	for (int i=0;i<8;i++){
		printf("%d        %s\n",i+1,chooseTimeSlot(i));
	}
	printf("\n");

	printf(" [test 7] Daily Time Slot Availability Check\n");
	printf("------------------------------------------------------------\n");
	printf(" it will base on current time %02d:%02d to judge\n",hour,minute);
	printf("\n");
	for( int i=0;i<8;i++){
		if(whetherTimePassed(i)){
			printf(" time slot %d: %s is passed(you can't reseve)\n",i+1,chooseTimeSlot(i));
		}
		else{printf(" time slot %d: %s has not yet passed(you can reseve)\n",i+1,chooseTimeSlot(i));
		}}
	printf("\n");

	printf(" [test 8] the nearly time you can book today\n");
	printf("------------------------------------------------------------\n");
	int nearly = firstAvailableTimeSlot();
	if (nearly == -1){
		printf(" the time was pass! you can't reseve any time slot today \n");
	}else {printf(" the nearly available time slot is: time slot %d:%s\n",nearly + 1,chooseTimeSlot(nearly));
	}
	printf("\n");

	printf(" [test 9] Determine whether the date is today\n");
	printf("------------------------------------------------------------\n");
	if(is_today(today)){
		printf("Today's Date: Correctly identified as today\n");
	}
	if(!is_today(day2)){
		printf("Date of tomorrow: Correctly identified as not today\n");
	}printf("\n");
	printf("============================================================\n");
	printf("         every test is finish!\n");
    return 0;
}

