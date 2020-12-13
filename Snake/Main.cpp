#include <iostream>
#include <graphics.h>
using namespace std;

int main()
{
	initgraph(640, 480);
	setbkcolor(RGB(207, 214, 229));
	cleardevice();
	//ÉèÖÃÌî³äÑÕÉ«
	setfillcolor(YELLOW);
	//»­¾ØĞÎ
	fillrectangle(0, 0, 10, 10);
	system("pause");
	return 0;
}