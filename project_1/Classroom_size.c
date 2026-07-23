#include "room_booking.h"

// date setting
char g_dateList[DATE_TOTAL][DATE_STR_LEN] = {
    "2026.07.20",
    "2026.07.21",
    "2026.07.22"
};

//to check if the room is free?

int isRoomFree(const char* roomId, int dateIdx, int slotIdx) {
    if (!roomId || dateIdx < 0 || dateIdx >= DATE_TOTAL || slotIdx < 0 || slotIdx >= SLOT_TOTAL)
        return 0;
    RoomAllStatus status;
    loadRoomStatus(roomId, &status, g_dateList);
    return status.dateStatus[dateIdx][slotIdx].isBooked == 0;
}

int bookSlot(const char* roomId, int dateIdx, int slotIdx, const char* userName) {
    if (!roomId || !userName || dateIdx < 0 || dateIdx >= DATE_TOTAL || slotIdx < 0 || slotIdx >= SLOT_TOTAL)
        return 0;
    // cheak the free
    if (!isRoomFree(roomId, dateIdx, slotIdx))
        return 0;
    RoomAllStatus status;
    loadRoomStatus(roomId, &status, g_dateList);
    RoomSlotStatus* target = &status.dateStatus[dateIdx][slotIdx];
    target->isBooked = 1;
    strncpy(target->bookUser, userName, USER_NAME_LEN-1);
    target->bookUser[USER_NAME_LEN-1] = '\0';
    strncpy(target->dateStr, g_dateList[dateIdx], DATE_STR_LEN-1);
    target->dateStr[DATE_STR_LEN-1] = '\0';
    saveRoomStatus(&status);
    return 1;
}

//to find some room to user

int findAvailableRoom(Classroom rooms[], int roomCount, int dateIdx, int slotIdx, int minCapacity) {
    int best = -1;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].capacity >= minCapacity && isRoomFree(rooms[i].roomId, dateIdx, slotIdx)) {
            if (best == -1 || rooms[i].capacity < rooms[best].capacity) {
                best = i;
            }
        }
    }
    return best;
}

//let user enter the room size.

int inputRoomSize() {
    int size;
    int inputResult;
    do {
        printf("Input the size of classroom: ");
        inputResult = scanf("%d", &size);
        if (inputResult != 1) {
            while (getchar() != '\n');
            printf("Warning! Invalid input, please enter a number.\n");
        } else if (size <= 0) {
            printf("Size must be positive integer, please enter a positive integer.\n");
        }
    } while (inputResult != 1 || size <= 0);
    return size;
}


//to show if there is available book for user

void showBookingResult(const char* roomId, int success) {
    if (success) {
        printf("Classroom %s is available now, you can book it.\n", roomId);
    } else {
        printf("No available room!\n");
    }
}

//to comfirm the booking

int askContinue() {
    char reply;
    do {
        printf("Continue (y/n)? ");
        scanf(" %c", &reply);
        if (reply == 'y' || reply == 'Y') return 1;
        else if (reply == 'n' || reply == 'N') return 0;
        else {
            printf("Warning! Invalid input, please enter y(yes) or n(no).\n");
            while (getchar() != '\n');
        }
    } while (1);
}


//the main function of the booking system
int runBookingProcess(Classroom rooms[], int roomCount, int dateIdx, int slotIdx, char* userName) {
    int minSize = inputRoomSize();
    int idx = findAvailableRoom(rooms, roomCount, dateIdx, slotIdx, minSize);
    if (idx >= 0) {
        if (bookSlot(rooms[idx].roomId, dateIdx, slotIdx, userName)) {
            showBookingResult(rooms[idx].roomId, 1);
        } else {
            printf("Booking failed unexpectedly.\n");
        }
    } else {
        showBookingResult(NULL, 0);
    }
    return askContinue();
}
