#ifndef CLASS_SIZE_H
#define CLASS_SIZE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROOM 50
#define NAME_LENGTH 20
#define DATE_TOTAL 3
#define SLOT_TOTAL 9
#define DATE_STR_LEN 20
#define USER_NAME_LEN 20
#define FILE_NAME_BUF 100
#define LINE_BUF 256

typedef struct {
    char roomId[50];
    int capacity;
} ClassroomBase;

typedef struct {
    char dateStr[DATE_STR_LEN];
    int isBooked;
    char bookUser[USER_NAME_LEN];
} RoomSlotStatus;

typedef struct {
    char roomId[50];
    RoomSlotStatus dateStatus[DATE_TOTAL][SLOT_TOTAL];
} RoomAllStatus;

// ����ȫ�������б�����ĳ�� .c �ļ��ж��壩
extern char g_dateList[DATE_TOTAL][DATE_STR_LEN];

// ��������
int loadClassroomBase(ClassroomBase roomArr[]);
void initAllRoomFiles(ClassroomBase roomArr[], int roomCount, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void loadRoomStatus(const char* roomId, RoomAllStatus* statusOut, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void saveRoomStatus(const RoomAllStatus* statusIn);
int querySlotFree(const char* roomId, int dateIdx, int slotIdx);
int bookSlot(const char* roomId, int dateIdx, int slotIdx, const char* userName, const char* dateStr);

// ��һ�δ������õ��� Classroom �ṹ������� ClassroomBase ��ͬ���ɵ������壩
typedef struct {
    char classroom_number[50];
    int size;
} Classroom;

// ԤԼ���̺����������������Ĵ��룩
int isRoomFree(char *roomNo, int dayIndex, int slotIndex);
int bookRoomInFile(char *roomNo, int dayIndex, int slotIndex, char *userName);
int findAvailableRoom(Classroom classroom[], int room_order, int daySelect, int timeSelect, int minsize);
int inputRoomSize();
void showBookingResult(char *classroom_number, int freeroom);
int askContinue();
int runBookingProcess(Classroom classroom[], int room_order, int daySelect, int timeSelect, char *user_name);

void trimLine(char* str);
void getRoomFileName(const char* roomId, char* fileNameOut);

#endif
