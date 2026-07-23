#include <stdio.h>

#define MAX_ROOM 50//self define (need to change if different from part 3)
#define NAME_LENGTH 20
#define DAY_ORDER 3
#define TIME_ORDER 9
typedef struct{//basic information of classroom
	char classroom_number[50];
	int size;
}Classroom;
int isRoomFree(char *classroom_number, int daySelect, int timeSelect);//determine whether the selected room is free
int bookRoomInFile(char *classroom_number, int daySelect, int timeSelect, char *user_name);//record the booking status in the file 
int findAvailableRoom(Classroom classroom[], int room_order, int daySelect, int timeSelect, int minsize);//return the available room
int inputRoomSize();//input the size of classroom, return the valid number of person
void showBookingResult(char *classroom_number, int freeroom);//show the result of booking
int askContinue();
int runBookingProcess(Classroom classroom[], int room_order, int daySelect, int timeSelect, char *user_name);





/*int isRoomFree(char *roomNo, int dayIndex, int slotIndex) {
    return 1;}
int bookRoomInFile(char *roomNo, int dayIndex, int slotIndex, char *userName) {
    printf("[Test] Book %s, day %d, slot %d, user: %s\n", roomNo, dayIndex, slotIndex, userName);
    return 1;
}

int main(int argc, char *argv[])
{
    Classroom rooms[] = {
        {"C1",30}, {"C2",30}, {"C3",50}, {"C4",50},
        {"C5",50}, {"C6",70}, {"C7",80}, {"C8",80},
        {"C9",80}, {"C10",100}, {"C11",100}, {"C12",100}
    };
    int roomCount = 12;
    char userName[] = "alice";
    int goOn;
    do {
        goOn = runBookingProcess(rooms, roomCount, 1, 3, userName);
    } while (goOn == 1);

    

    return 0;
}*/

int findAvailableRoom(Classroom classroom[], int room_order, int daySelect, int timeSelect, int minsize){
    int i;
    int availableselect = -1;//Index of best match; -1 means no qualified room initially
    for(i = 0; i < room_order; i++){//check all classrooms to find optimal match
        if((isRoomFree(classroom[i].classroom_number, daySelect, timeSelect) == 1) && (classroom[i].size >= minsize)){//check if current room is free and meets minimum capacity requirement
		if(availableselect == -1){
           availableselect = i;}
        else if(classroom[i].size < classroom[availableselect].size){
           availableselect = i;}}}//find a smaller qualified room update to this better match
    return availableselect;}

int inputRoomSize(){
    int size;
	int inputresult;
	do{
		printf("Input the size of classroom: ");
		inputresult = scanf("%d", &size);
		if(inputresult != 1){//flush all remaining characters in input buffer to avoid infinite loop
			while(getchar() != '\n');
			printf("Warning! Invalid input, please enter a number.\n");}
		else if(size <= 0){
			printf("Size must be positive integer, please enter a positive integer.\n");}}
    while(inputresult != 1 || size <= 0);//keep prompting until valid positive integer is entered
	return size;}

void showBookingResult(char *classroom_number, int freeroom){
	if(freeroom == 1){
		printf("Classroom %s is available now, you can book it.\n", classroom_number);}
	else{
		printf("No available room!\n");}}

int askContinue(){
	char reply;
	do{
		printf("Continue (y/n)? ");
		scanf(" %c", &reply);
		if(reply == 'y' || reply == 'Y'){//consider the users may not convert capitalization to lowercase
			return 1;}
		else if(reply == 'n' || reply == 'N'){
			return 0;}
		else{
			printf("Warning! Invalid input, please enter y(yes) or n(no).\n");
			while(getchar() != '\n');}}
	while(1);}//Infinite loop until valid y/n is received

int runBookingProcess(Classroom classroom[], int room_order, int daySelect, int timeSelect, char *user_name){
    int size = inputRoomSize();
    int available_Index = findAvailableRoom(classroom, room_order, daySelect, timeSelect, size);
    if(available_Index >= 0){
	   bookRoomInFile(classroom[available_Index].classroom_number, daySelect, timeSelect,user_name);//submit booking record to file system
	   showBookingResult(classroom[available_Index].classroom_number, 1);}//display successful booking result
    else{
	   showBookingResult(NULL, 0);}//display there is no available room
    return askContinue();}//ask user whether to start another booking


