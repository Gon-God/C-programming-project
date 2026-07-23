#include <stdio.h>
#include <stdlib.h>
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



void wait_for_enter(void) {
    int c;
	printf("Enter to continues...");
    // 不断读取字符，直到遇到换行符或文件结束，清空残留的缓冲区
    while ((c = getchar()) != '\n' && c != EOF) { }
    // 现在缓冲区干净了，再次等待用户按回车
    getchar();
}
