#include "Windows.h"
#include "method.h"
void gotoxy(int x,int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X=x;
	pos.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,pos);
}
void color(short x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}
void colorSet(short x,short y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),y*16+x);
}
