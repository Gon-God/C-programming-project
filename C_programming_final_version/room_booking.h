#ifndef ROOM_BOOKING_H
#define ROOM_BOOKING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//base setting for the system

#define MAX_ROOM         50
#define DATE_TOTAL       3
#define SLOT_TOTAL       9
#define USER_NAME_LEN    21
#define DATE_STR_LEN     20
#define ROOM_ID_LEN      10      
#define FILE_NAME_BUF    64
#define LINE_BUF         256

//the struct of classroom
typedef struct {
    char roomId[ROOM_ID_LEN];
    int capacity;
} Classroom;           


//the room now
typedef struct {
    char dateStr[DATE_STR_LEN];
    int isBooked;      
    char bookUser[USER_NAME_LEN];
} RoomSlotStatus;

typedef struct {
    char roomId[ROOM_ID_LEN];
    RoomSlotStatus dateStatus[DATE_TOTAL][SLOT_TOTAL];
} RoomAllStatus;

extern char g_dateList[DATE_TOTAL][DATE_STR_LEN];


void trimLine(char* str);
void getRoomFileName(const char* roomId, char* fileNameOut);

int loadClassroomBase(Classroom roomArr[]);
void initAllRoomFiles(Classroom roomArr[], int roomCount, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void refreshRoomFileWithNewDate(Classroom roomArr[], int roomCnt, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void loadRoomStatus(const char* roomId, RoomAllStatus* statusOut, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void saveRoomStatus(const RoomAllStatus* statusIn);

int isRoomFree(const char* roomId, int dateIdx, int slotIdx);
int bookSlot(const char* roomId, int dateIdx, int slotIdx, const char* userName);
int findAvailableRoom(Classroom rooms[], int roomCount, int dateIdx, int slotIdx, int minCapacity);
int runBookingProcess(Classroom rooms[], int roomCount, int dateIdx, int slotIdx, char* userName);
void showBookingResult(const char* roomId, int success);
int askContinue();

//new
void generateDateListFromSystem();
int showDateMenu();
#endif

//for two Classroom.c files.
