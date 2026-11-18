#include "room_booking.h"


//to open the file.
int loadClassroomBase(Classroom roomArr[]) {
    if (!roomArr) {
        printf("Error: room array pointer is NULL!\n");
        return 0;
    }
    FILE* fp = fopen("classroom_info.txt", "r");
    if (!fp) {
        printf("Error: Cannot open classroominfo.txt\n");
        return 0;
    }
    int count = 0;
    char line[LINE_BUF];
    while (fgets(line, sizeof(line), fp)) {
        trimLine(line);
        if (strlen(line) == 0) continue;
        if (sscanf(line, "%s %d", roomArr[count].roomId, &roomArr[count].capacity) == 2) {
            count++;
            if (count >= MAX_ROOM) {
                printf("Warning: Reach max room limit %d, stop loading\n", MAX_ROOM);
                break;
            }
        }
    }
    fclose(fp);
    return count;
}

//to create the room txt

void initSingleRoomFile(const char* roomId, char dateList[DATE_TOTAL][DATE_STR_LEN]) {
    char fileName[FILE_NAME_BUF];
    getRoomFileName(roomId, fileName);
    FILE* fp = fopen(fileName, "w");
    if (!fp) {
        printf("Warning: Failed to create file %s\n", fileName);
        return;
    }
    fprintf(fp, "RoomID: %s\n", roomId);
    for (int d = 0; d < DATE_TOTAL; d++) {
        for (int s = 0; s < SLOT_TOTAL; s++) {
            fprintf(fp, "Date:%s Slot:%d Status:0 User:\n", dateList[d], s);
        }
    }
    fclose(fp);
}

void initAllRoomFiles(Classroom roomArr[], int roomCount, char dateList[DATE_TOTAL][DATE_STR_LEN]) {
    if (!roomArr || !dateList || roomCount <= 0) {
        printf("Error: Invalid param for initAllRoomFiles\n");
        return;
    }
    for (int i = 0; i < roomCount; i++) {
        initSingleRoomFile(roomArr[i].roomId, dateList);
    }
}



void refreshRoomFileWithNewDate(Classroom roomArr[], int roomCnt, char dateList[DATE_TOTAL][DATE_STR_LEN])
{
    for (int r = 0; r < roomCnt; r++)
    {
        const char* rid = roomArr[r].roomId;
        RoomAllStatus oldStatus;

        loadRoomStatus(rid, &oldStatus, dateList);


        RoomAllStatus newStatus;
        memset(&newStatus, 0, sizeof(RoomAllStatus));
        strncpy(newStatus.roomId, rid, ROOM_ID_LEN - 1);
        newStatus.roomId[ROOM_ID_LEN - 1] = '\0';

        for (int d = 0; d < DATE_TOTAL; d++)
        {
            for (int s = 0; s < SLOT_TOTAL; s++)
            {
                strncpy(newStatus.dateStatus[d][s].dateStr, dateList[d], DATE_STR_LEN - 1);
                newStatus.dateStatus[d][s].dateStr[DATE_STR_LEN - 1] = '\0';
                newStatus.dateStatus[d][s].isBooked = 0;
                newStatus.dateStatus[d][s].bookUser[0] = '\0';
            }
        }
        for (int oldD = 0; oldD < DATE_TOTAL; oldD++)
        {
            for (int s = 0; s < SLOT_TOTAL; s++)
            {
                if (oldStatus.dateStatus[oldD][s].isBooked == 1)
                {
                    char* oldDate = oldStatus.dateStatus[oldD][s].dateStr;

                    for (int newD = 0; newD < DATE_TOTAL; newD++)
                    {
                        if (strcmp(oldDate, dateList[newD]) == 0)
                        {
                            newStatus.dateStatus[newD][s].isBooked = 1;
                            strncpy(newStatus.dateStatus[newD][s].bookUser, oldStatus.dateStatus[oldD][s].bookUser, USER_NAME_LEN - 1);
                            newStatus.dateStatus[newD][s].bookUser[USER_NAME_LEN - 1] = '\0';
                        }
                    }
                }
            }
        }
       
        saveRoomStatus(&newStatus);
    }
}





//to load the room status

void loadRoomStatus(const char* roomId, RoomAllStatus* statusOut, char dateList[DATE_TOTAL][DATE_STR_LEN]) {
    if (!roomId || !statusOut || !dateList) return;
    memset(statusOut, 0, sizeof(RoomAllStatus));
    strncpy(statusOut->roomId, roomId, sizeof(statusOut->roomId) - 1);
    statusOut->roomId[sizeof(statusOut->roomId)-1] = '\0';

    char fileName[FILE_NAME_BUF];
    getRoomFileName(roomId, fileName);
    FILE* fp = fopen(fileName, "r");
    if (!fp) {
        printf("Warning: Cannot open %s, keep empty status\n", fileName);
        return;
    }
    char line[LINE_BUF];
    fgets(line, sizeof(line), fp); //       ?   "RoomID: ..."
    trimLine(line);

    char dateBuf[DATE_STR_LEN];
    int slot, stat;
    char userBuf[USER_NAME_LEN];
    while (fgets(line, sizeof(line), fp)) {
        trimLine(line);
        if (strlen(line) == 0) continue;
        int ret = sscanf(line, "Date:%s Slot:%d Status:%d User:%s", dateBuf, &slot, &stat, userBuf);
        if (ret < 3) continue; 
        // find the date index
        int dIdx = -1;
        for (int d = 0; d < DATE_TOTAL; d++) {
            if (strcmp(dateBuf, dateList[d]) == 0) {
                dIdx = d;
                break;
            }
        }
        if (dIdx == -1 || slot < 0 || slot >= SLOT_TOTAL) continue;
        strncpy(statusOut->dateStatus[dIdx][slot].dateStr, dateBuf, DATE_STR_LEN-1);
        statusOut->dateStatus[dIdx][slot].isBooked = stat;
        if (ret == 4) { // text the user
            strncpy(statusOut->dateStatus[dIdx][slot].bookUser, userBuf, USER_NAME_LEN-1);
        } else {
            statusOut->dateStatus[dIdx][slot].bookUser[0] = '\0';
        }
    }
    fclose(fp);
}

//to save the room status after the booking

void saveRoomStatus(const RoomAllStatus* statusIn) {
    if (!statusIn) return;
    char fileName[FILE_NAME_BUF];
    getRoomFileName(statusIn->roomId, fileName);
    FILE* fp = fopen(fileName, "w");
    if (!fp) {
        printf("Error: Write file %s failed\n", fileName);
        return;
    }
    fprintf(fp, "RoomID:%s\n", statusIn->roomId);
    for (int d = 0; d < DATE_TOTAL; d++) {
        for (int s = 0; s < SLOT_TOTAL; s++) {
            const RoomSlotStatus* st = &statusIn->dateStatus[d][s];
            fprintf(fp, "Date:%s Slot:%d Status:%d User:%s\n",
                    st->dateStr, s, st->isBooked, st->bookUser);
        }
    }
    fclose(fp);
}

void trimLine(char* str) {
    if (str == NULL) return;
    size_t len = strlen(str);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
}

//to make it usable to "Classroom_size.c"

void getRoomFileName(const char* roomId, char* fileNameOut) {
    snprintf(fileNameOut, FILE_NAME_BUF, "%s.txt", roomId);
}
