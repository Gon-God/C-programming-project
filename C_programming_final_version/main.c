#include "common.h"

int main(int argc, char *argv[])
{

//This part is to check the account and the password.
    char account[100];
	int login_status;


/*loginSystem return 1 means login in successfully.
	Return 0 means cannot login in.*/
    login_status = loginSystem(account);


//exit the system.
	if (login_status == 0)
		return 0;
	else {wait_for_enter();}

	clear_screen();

//Load the classroom imformation
    Classroom rooms[MAX_ROOM];
    int roomCount = loadClassroomBase(rooms);
    if (roomCount == 0) {
        printf("No classroom data found. Please ensure classroominfo.txt exists.\n");
        return 1;
    }
//new
generateDateListFromSystem();
refreshRoomFileWithNewDate(rooms, roomCount, g_dateList);


//The main system
	int goOn = 1;
    while (goOn) {
        // show the date menu
        int dateIdx = showDateMenu();
        if (dateIdx == -1) {
            printf("Exit requested.\n");
            break; //exit the system
        }
		
		clear_screen();

        // show the available time period
        int isToday = (dateIdx == 0) ? 1 : 0;
        int slotIdx = showTimeSlotMenu(isToday);
        if (slotIdx == -1) {
            printf("Exit requested.\n");
			wait_for_enter();
			clear_screen();
            continue;  // go back to the date manu
        }

        //find an available classroom, and make a booking
        goOn = runBookingProcess(rooms, roomCount, dateIdx, slotIdx, account);
		
		clear_screen();
        // runBookingProcess return 1 to continue, return 0 to exit
    }

    return 0;
}
