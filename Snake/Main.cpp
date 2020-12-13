#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <graphics.h>

#define MAX_SNAKE 500 //蛇的最大节数
#define WIN_WIDTH 640
#define WIN_HEIGHT 480

using namespace std;

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Food
{
	int x;
	int y;
	DWORD color;
	bool flag; //是否被吃掉，是否需要重新生成
}food;
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
	//初始化蛇
	srand(time(NULL));
	snake.num = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.size = 10;
	snake.speed = 10;
	
	snake.coor[0].x = 20;
	snake.coor[0].y = 0;
	snake.coor[0].color = RGB(rand() % 256, rand() % 256, rand() % 256);	
	
	snake.coor[1].x = 10;
	snake.coor[1].y = 0;
	snake.coor[1].color = RGB(rand() % 256, rand() % 256, rand() % 256);	
	
	snake.coor[2].x = 0;
	snake.coor[2].y = 0;
	snake.coor[2].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	//初始化食物
	food.x = rand() % (WIN_WIDTH / 10) * 10;
	food.y = rand() % (WIN_HEIGHT / 10) * 10;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.flag = true;
}

void gameDraw()
{
	cleardevice();
	
	//绘制蛇
	for (int i = 0; i < snake.num; i++)
	{
		//设置填充颜色
		setfillcolor(snake.coor[i].color);
		//画矩形
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + 10, snake.coor[i].y + 10);

	}

	//绘制食物
	if (food.flag == true)
	{
		setfillcolor(food.color);
		solidellipse(food.x, food.y, food.x + 10, food.y + 10);

	}

	//绘制分数
	char score[20];
	sprintf_s(score, "分数： %d", snake.num);
	outtextxy(WIN_WIDTH - 100, 50, score);
	settextcolor(RED);
	
}

void gameMove()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.speed;
		break;

	case DOWN:
		snake.coor[0].y += snake.speed;
		break;

	case LEFT:
		snake.coor[0].x -= snake.speed;
		break;

	case RIGHT:
		snake.coor[0].x += snake.speed;
		break;

	default:
		break;
	}
}

void gameCtrl()
{
	//获取键盘输入
	char key = _getch();
	//cout << key << endl;
	switch (key)
	{
	case 72:
		if (snake.dir != DOWN)
		{
			snake.dir = UP;
		}
		break;
	case 80:
		if (snake.dir != UP)
		{
			snake.dir = DOWN;
		}
		break;
	case 75:
		if (snake.dir != RIGHT)
		{
			snake.dir = LEFT;
		}
		break;
	case 77:
		if (snake.dir != LEFT)
		{
			snake.dir = RIGHT;
		}
		break;
	case ' ':
		MessageBox(NULL, "暂停", "snake", MB_OK);
	default:
		break;
	}
}

void creatFood()
{
	if (!food.flag)
	{
		//初始化食物
		food.x = rand() % (WIN_WIDTH / 10) * 10;
		food.y = rand() % (WIN_HEIGHT / 10) * 10;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.flag = true;
	}
}
void eatFood()
{
	if (food.flag == true && snake.coor[0].x == food.x && snake.coor[0].y == food.y)
	{
		food.flag = false;
		snake.coor[snake.num++].color = food.color;
		creatFood();
	}
}

void fail()
{
	int code = MessageBox(NULL, "好菜啊弟弟,再来？", "失败", MB_YESNO);
	switch (code)
	{
	case IDYES:
		gameInit();
		break;
	case IDNO:
		exit(0);
		break;
	default:
		break;
	}
}
void gameFail()
{
	if (snake.coor[0].x < 0 || snake.coor[0].x > WIN_WIDTH || snake.coor[0].y < 0 || snake.coor[0].y > WIN_HEIGHT)
	{
		fail();
	}
}
int main()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	setbkcolor(RGB(207, 214, 229));
	cleardevice();//刷新窗口
	
	gameInit();
	while (1)
	{
		gameDraw();
		gameMove(); 
		if (_kbhit())
		{
			gameCtrl();

		}
		eatFood();
		gameFail();
		Sleep(100);
	}
	finally:system("exit");
	return 0;
}