#ifndef COMMOM_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ROOMN      50
#define DATE_TOTAL     3
#define SLOT_TOTAL     9
#define USER_NAME_LEN  21
#define DATE_STR_LEN   20
#define FILE_NAME_BUF  64
#define LINE_BUF       256

//basic information of classroom
typedef struct{
    char roomId[10];
    int capacity;
}ClassroomBase;
//book information of single date
typedef struct{
    char dateStr[DATE_STR_LEN];
	int isBooked//0 means free,1 means occupied
    char bookUser[USER_NAME_LEN];
}RoomSlotStatus;
//information of single classroom of 3 dates
typedef struct{
	char roomId[10];
	RoomSlotStatus dateStatus[DATE_TOTAL][SLOT_TOTAL];
}RoomAllStatus;
//           indicate of the function in mode 3
//loading classroom basic information
int loadClassroomBase(ClassroomBase roomArr[]);
//initializing all classroom file 
void initAllRoomFiles(ClassroomBase roomArr[],int roomCount,char dateList[DATE_TOTAL][DATE_STR_LEN]);
//reading all single classroom to struct
void loadRoomStatus(const char*roomId,RoomAllStstus* statusOut,char dateList[DATE_TOTAL][DATE_STR_LEN]);
//save room status
void saveRoomStatus(const RoomAllStatus* statusIn);
//check date whether is free:0 means free,1 means occupied
int querySlotFree(const char*roomId,int dateIdx,int slotIdx);
//book date:successful return means 1 and occupied means 0
int bookSlot(const char* roomId,int dateIdx,int slotIdx,const char* userName,const char*dateStr);
//decrease \r and \n
static inline void trimLine(char* str);

#endif




