/****************************************************************************
 *                                                                          *
 * File    : main.c                                                         *
 *                                                                          *
 * Purpose : Console mode (command line) program.                           *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

#include "menu.h"
#include <stdio.h>
#include <time.h>
#include "main_h.h"

// get current hour 0-23
static int getCurrentHour(void)
{
    time_t now;
    time(&now);
    struct tm *t = localtime(&now);
    return t->tm_hour;
}

// show date choose menu, return 0=today,1=tomorrow,2=day after,-1=exit
int showDateMenu(void)
{
    time_t now;
    time(&now);
    struct tm *t = localtime(&now);

    int year = t->tm_year + 1900;
    int mon = t->tm_mon + 1;
    int day = t->tm_mday;
	

	printf("Welcome to Classroom Booking System!\n");
	printf("Choose an available date:\n");
    printf("Date Menu\n");
    printf("1.Date (%d/%02d/%02d)\n", year, mon, day);
    printf("2.Date (%d/%02d/%02d)\n", year, mon, day + 1);
    printf("3.Date (%d/%02d/%02d)\n", year, mon, day + 2);
    printf("4.Exit\n");
    printf("Enter your choice (1-4): ");

    int op;
    while(scanf("%d", &op) != 1 || op < 1 || op > 4)
    {
        // clear buffer
        while(getchar() != '\n');
        printf("Wrong input, input 1-4 again: ");
    }
    while(getchar() != '\n');

    if(op == 1) return 0;
    if(op == 2) return 1;
    if(op == 3) return 2;
    return -1;
}

// show time slot menu, isToday=1 filter past time
int showTimeSlotMenu(int isToday)
{
    const char *timeList[] = {
        "9:00 am 每 9:50 am",
        "10:00 am 每 10:50 am",
        "11:00 am 每 11:50 am",
        "12:00 pm 每 12:50 pm",
        "13:00 pm 每 13:50 pm",
        "14:00 pm 每 14:50 pm",
        "15:00 pm 每 15:50 pm",
        "16:00 pm 每 16:50 pm"
    };

    int curH = getCurrentHour();
    int start = 0;
    if(isToday == 1)
    {
        if(curH >= 16) start = 8;
        else if(curH >= 15) start = 7;
        else if(curH >= 14) start = 6;
        else if(curH >= 13) start = 5;
        else if(curH >= 12) start = 4;
        else if(curH >= 11) start = 3;
        else if(curH >= 10) start = 2;
        else if(curH >= 9) start = 1;
    }
	
    printf("Time Slot Menu\n");
    int num = 1;
    int map[9];
    int count = 0;
    for(int i = start; i < 8; i++)
    {
        printf("%d. %s\n", num, timeList[i]);
        map[count++] = i;
        num++;
    }
    printf("%d. Exit\n", num);
    printf("Enter choice: ");

    int sel;
    int maxSel = count + 1;
    while(scanf("%d", &sel) != 1 || sel < 1 || sel > maxSel)
    {
        while(getchar() != '\n');
        printf("Invalid number, input again: ");
    }
    while(getchar() != '\n');


    if(sel == maxSel)
        return -1;
    return map[sel - 1];
}

/*
// test main,final test will be comment
int main(void)
{
    int dateSel = showDateMenu();
    printf("date return: %d\n", dateSel);
    if(dateSel != -1)
    {
        int t = showTimeSlotMenu(dateSel == 0 ? 1 : 0);
        printf("slot return: %d\n", t);
    }
    return 0;
}
*/


