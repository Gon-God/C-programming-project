#include <stdio.h>
#include <stdlib.h>

//to clear thr screen, diffenent by Win and Linux/Mac
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


//To wait for the enter.
void wait_for_enter(void) {
    int c;
	printf("Enter to continues...");
    while ((c = getchar()) != '\n' && c != EOF) { }
    getchar();
}
