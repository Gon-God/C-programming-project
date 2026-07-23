#ifndef ROOM_BOOKING_H
#define ROOM_BOOKING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* �������� */
#define MAX_ROOM         50
#define DATE_TOTAL       3
#define SLOT_TOTAL       9
#define USER_NAME_LEN    21
#define DATE_STR_LEN     20
#define ROOM_ID_LEN      10      // ͳһ����ID����
#define FILE_NAME_BUF    64
#define LINE_BUF         256

/* ���Ͷ��� */
typedef struct {
    char roomId[ROOM_ID_LEN];
    int capacity;
} Classroom;           // �ϲ� ClassroomBase �� Classroom

typedef struct {
    char dateStr[DATE_STR_LEN];
    int isBooked;       // 0 ���У�1 ��Ԥ��
    char bookUser[USER_NAME_LEN];
} RoomSlotStatus;

typedef struct {
    char roomId[ROOM_ID_LEN];
    RoomSlotStatus dateStatus[DATE_TOTAL][SLOT_TOTAL];
} RoomAllStatus;

/* ȫ�������б�����ĳ�� .c �ж��壩 */
extern char g_dateList[DATE_TOTAL][DATE_STR_LEN];


void trimLine(char* str);
void getRoomFileName(const char* roomId, char* fileNameOut);

/* ---------- I/O ���� ---------- */
int loadClassroomBase(Classroom roomArr[]);
void initAllRoomFiles(Classroom roomArr[], int roomCount, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void loadRoomStatus(const char* roomId, RoomAllStatus* statusOut, char dateList[DATE_TOTAL][DATE_STR_LEN]);
void saveRoomStatus(const RoomAllStatus* statusIn);

/* ---------- ҵ���� ---------- */
int isRoomFree(const char* roomId, int dateIdx, int slotIdx);
int bookSlot(const char* roomId, int dateIdx, int slotIdx, const char* userName);
int findAvailableRoom(Classroom rooms[], int roomCount, int dateIdx, int slotIdx, int minCapacity);
int runBookingProcess(Classroom rooms[], int roomCount, int dateIdx, int slotIdx, char* userName);
void showBookingResult(const char* roomId, int success);
int askContinue();

;
#endif
