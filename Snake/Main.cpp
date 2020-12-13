#include <iostream>
#include <graphics.h>
#define MAX_SNAKE 500 //蛇的最大节数
using namespace std;

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Pos
{
	int x;
	int y;
	DWORD color;
};
struct Snake
{
	int num;     //当前节数
	int dir;     //蛇的方向
	int score;   //分数
	int size;    //蛇的宽和高
	int speed;   //速度
	//表示每一节蛇的坐标 数组
	struct Pos coor[MAX_SNAKE];
}snake;

void gameInit()
{
	srand(time(NULL));
	snake.num = 1;
	snake.dir = UP;
	snake.score = 0;
	snake.size = 10;
	snake.speed = 10;
	snake.coor[0].x = 0;
	snake.coor[0].y = 0;
	snake.coor[0].color = RGB(rand() % 256, rand() % 256, rand() % 256);
}
int main()
{
	initgraph(640, 480);
	setbkcolor(RGB(207, 214, 229));
	cleardevice();//刷新窗口
	
	gameInit();

	//设置填充颜色
	setfillcolor(snake.coor[0].color);
	//画矩形
	fillrectangle(snake.coor[0].x, snake.coor[0].y, 10, 10);
	//画圆形
	fillcircle(20, 20, 10);
	system("pause");
	return 0;
}