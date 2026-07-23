#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ROOM       50
#define DATE_TOTAL     3
#define SLOT_TOTAL     9
#define USER_NAME_LEN  21
#define DATE_STR_LEN   20
#define FILE_NAME_BUF  64
#define LINE_BUF       256

typedef struct {
    char roomId[10];
    int capacity;
} ClassroomBase;

typedef struct {
    char dateStr[DATE_STR_LEN];
    int isBooked;      // 0 free, 1 occupied
    char bookUser[USER_NAME_LEN];
} RoomSlotStatus;

typedef struct {
    char roomId[10];
    RoomSlotStatus dateStatus[DATE_TOTAL][SLOT_TOTAL];
} RoomAllStatus;

int loadClassroomBase(ClassroomBase roomArr[]);
void initAllRoomFiles(ClassroomBase roomArr[], int roomCount, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void loadRoomStatus(const char* roomId, RoomAllStatus* statusOut, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void saveRoomStatus(const RoomAllStatus* statusIn);
int querySlotFree(const char* roomId, int dateIdx, int slotIdx);
int bookSlot(const char* roomId, int dateIdx, int slotIdx, const char* userName, const char* dateStr);
static inline void trimLine(char* str);

#endif
