#include <windows.h>//宏定义颜色 
#define RED FOREGROUND_RED | FOREGROUND_INTENSITY
#define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define YELLOW FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define PURPLE FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define BLUE FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define LIGHT_BLUE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
HANDLE hOut;
void initHandle()//初始化句柄 
{
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
} 
void setColor(WORD wAttributes)//设置颜色函数 
{
	SetConsoleTextAttribute(hOut,wAttributes);
}
