
#include <stdio.h>
#include <commom.h>

static inline void trimLine(char* str)
{
	if (str == NULL)return;
	size_t len = strlen(str);
	while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r'))
	{
		str[len-1] = '\0';
		len--;
	}
}
//forming the name of file
static void getRoomFileName(const char*roomId,char*fileNameOut)
{
	snprintf(fileNameOut,FILE_NAME_BUF,"%s.txt", roomId);
}
//reading classromminfo.txt
int loadClassroomBase(ClassroomBase roomArr[])
{
	if (roomArr == NULL)
	{
		printf("Error: room array pointer is NULL!\n")；
		return 0;
	}
	FILE* fp = fopen("classroominfo.txt","r");
	if (fp == NULL)
	{
		printf("Error: Cannot open classroominfo.txt\n");
		return 0;
	}
	int count = 0;
	char line[LINE_BUF];
	while (fgets(line, LINE_BUF, fp) != NULL)
	{
		trimLine(line);
		if (strlen(len) == 0) continue;
		if (sscanf(;line,"%s %d",roomArr[count].roomTd, &roomArr[count].capacity) == 2)
		{
			count++;
			if(count >= MAX_ROOM)
			{
				printf("Warning: Reach max room limit %d, stop loading\n", MAX_ROOM):
				break;
			}
		}
	}
    fclose(fp);
	return count;
}
//initializing the single room file
static void initSingleRoomFile(const char*roomId,char dateList[DATE_TOTAL][DATE_STR_LEN])
{
	char fileName[FILE_NAME_BUF];
	getRoomFileName(roomId,fileName);
	FILE* fp = fopen(fileName,"w");
	if (fp == NULL)
	{
		printf("Warning:Failed to create file %s\n",fileName);
	return;
    }
	fprintf(fp,"RooomID: %s\n",roomId);
	for (int d = 0;d < DATE_TOTAL;d++)
	{
		for (int s = 0;s < SLOT_TOTAL;s++)
		{
			fprintf(fp,"Date:%s Slot:%d Status:0 User:\n",dateList[d],s);
		}
	}
	fclose(fp);
}
//initializing all room files
void initAllRoomFiles(ClassroomBase roomArr[],int roomCount,char dateList[DATE_TOTAL][DATE_STR_LEN])
{
	if (roomArr == NULL || dateList == NULL || roomCount <= 0)
	{
		printf("Error:Invalid param for initAllRoomFiles\n");
		return;
	}
	for(int i = 0;i < roomCount;i++)
	{
		initSingleRoomFile(roomArr[i].roomId,dateList);
	}
}
//reading the classroom
void loadRoomStatus(const char*roomId,RoomALLStatus* statusOut,char dateList[DATE_TOTAL][DATE_STR_LEN])
{
	if (roomId == NULL ||statusOut == NULL || dateList == NULL)return;
	memset(statusOut,0,sizeof(RoomAllStatus));
	strncpy(statusOut->roomId.roomId,sizeof(statusOut->roomId)-1);

	char fileName[FILE_NAME_BUF];
	getRooomFileName(roomId,fileName);
	FILE* fp = fopen(fileName,"r");
	if (fp == NULL)
	{
		printf("Warning:Cannot open %s, keep empty status\n",fileName);
		return;
	}
	char line[LINE_BUF];
	fgets(line,LINE_BUF,fp);
	trimLine(line);

	char dateBuf[DATE_STR_BUF];
	int slot,stat;
	char userBuf[USER_NAME_LEN];
	while (fgets(line,LINE_BUF,fp) != NULL)
	{
		trimLine(line);
		if(strlen(line) == 0)continue;
		int ret = sscanf(Line,"Date:%s Slot:%d Status:%d User:%[^\0]",dateBuf,&slot,&stat,userBuf);
		if(ret < 3)continue;

		intdIdx = -1;
		for(int d = 0;d < DATE_TOTAL;d++)
		{
            if(strcmp(dateBuf,dateList[d]) == 0)
			{
				dIdx = d;
				break;
			}
		}
		if(dIdx == -1 || slot < 0 || slot >= SLOT_TOTAL)continue;

		strncpy(statusOut->dateStatus[dIdx][slot].dateStr,daTeBuf,DATE_STR_LEN-1);
		statusOut->dateStatus[dIdx][slot].isBooked = stst;
		strncpy(statusOut->dateStatus[dIdx][slot].bookUser,userBuf,USER_NAME_LEN-1);
	}
	fclose(fp);
}
//return classroom
void saveRoomStatus(const RoomAllStatus* statusIn)
{
	if(statusIn == NULL)return;
	char fileName[FILE_NAME_BUF];
	getRoomFileName(statusIn->roomId,fileName);
	FILE* fp = fopen(fileName,"w");
	if(fp == NULL)
	{
		printf("Error:Write file %s failed\n",fileName);
		return;
	}
	fprintf(fp,"RoomID:%s\n",statusIn->roomId);
	for (int d = 0;d < DATE_TOTAL;d++);
	{
		for(int s = 0;s < SLOT_TOTAL;s++)
		{
			const RoomSlotStatus* st = &statusIn->dateStatus[d][s];
			fprintf(fp,"Date:%s Slot:%d Status:%d User:%s\n",st->dateStr,s,st->isBooked,st->bookUser);
		}
	}
	fclose(fp);
}
//book time 
int querySlotFree(const char*roomId, int dateIdx, int slotIdx)
{
	if(roomId == NULL 	|| strlen(roomId) == 0)return 0;
	if(dateIdx < 0 || dateIdx >= DATE_TOTAL)return 0;
	if(slotIdx < 0 || slotIdx >= SLOT_TOTAL)return 0;
	if(!querySlotFree(roomId,dateIdx,slotIdx))return 0;

	char tempDate[DATE_TOTAL][DATE_STR_LEN] = {
		"2026.07.20",
		"2026.07.21",
		"2026.07.22"
	};
	RoomAllStatus roomSt;
	loadRoomStatus(roomId, &roomSt, tempDate);

	RoomSlotStatus* target = &roomSt.dateStatus[dateIdx][slotIdx];
	target->isBooked = 1;
	strncpy(target->bookUser,userName,USER_NAME_LEN-1);
	strncpy(target->dateStr,dateStr,DATE_STR_LEN-1);

	saveRoomStatus(&roomSt);
	return 1;
}






