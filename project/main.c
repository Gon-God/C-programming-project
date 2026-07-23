
#include "main_h.h"

int main(int argc, char *argv[])
{

//This part is to check the account and the password.
    char account[100];
	int login_status;
    printf("Acount and password module test\n");

/*loginSystem return 1 means login in successfully.
	Return 0 means cannot login in.*/
    login_status = loginSystem(account);


//exit the system.
	if (login_status == 0)
		return 0;


//This part is to show the data menu.
    int dateSel = showDateMenu();

// show date choose menu, return 0=today,1=tomorrow,2=day after,-1=exit

    printf("date return: %d\n", dateSel);
    if(dateSel != -1)
    {
        int t = showTimeSlotMenu(dateSel == 0 ? 1 : 0);
        printf("slot return: %d\n", t);
    }


    return 0;
}

