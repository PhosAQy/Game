#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <graphics.h>

#define MAX_SNAKE 500 //�ߵ�������
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
int COUNT = 0;

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
	bool flag; //�Ƿ񱻳Ե����Ƿ���Ҫ��������
}food;
struct BigFood
{
	int x;
	int y;
	DWORD color;
	bool flag; //�Ƿ����
}bigFood;

struct Pos
{
	int x;
	int y;
	DWORD color;
};
struct Snake
{
	int num;     //��ǰ����
	int dir;     //�ߵķ���
	int score;   //����
	int size;    //�ߵĿ�͸�
	int speed;   //�ٶ�
	//��ʾÿһ���ߵ����� ����
	struct Pos coor[MAX_SNAKE];
}snake;

void gameInit()
{
	//��ʼ����
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

	
	//��ʼ��ʳ��
	food.x = rand() % (WIN_WIDTH / 10) * 10;
	food.y = rand() % (WIN_HEIGHT / 10) * 10;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.flag = true;

	do
	{
		bigFood.x = rand() % (WIN_WIDTH / 10) * 10;
		bigFood.y = rand() % (WIN_HEIGHT / 10) * 10;
	} while (bigFood.x == food.x && bigFood.y == food.y);
	bigFood.flag = false;
	if (rand() % 5 < 1)
	{
		bigFood.flag = true;
	}
}

void gameDraw()
{
	cleardevice();
	
	//������
	for (int i = 0; i < snake.num; i++)
	{
		//���������ɫ
		setfillcolor(snake.coor[i].color);
		//������
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + 10, snake.coor[i].y + 10);

	}

	//����ʳ��
	if (food.flag)
	{
		setfillcolor(food.color);
		solidellipse(food.x, food.y, food.x + 10, food.y + 10);

	}

	if (bigFood.flag)
	{
		setfillcolor(bigFood.color);
		solidellipse(bigFood.x, bigFood.y, bigFood.x + 20, bigFood.y + 20);
	}
	//���Ʒ���
	char score[20];
	sprintf_s(score, "������ %d", snake.num);
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
	//��ȡ��������
	char key = _getch();
	//cout << key << endl;
	switch (key)
	{
	case 72:
	case 'w':
		if (snake.dir != DOWN)
		{
			snake.dir = UP;
		}
		break;
	case 80:
	case 's':
		if (snake.dir != UP)
		{
			snake.dir = DOWN;
		}
		break;
	case 75:
	case 'a':
		if (snake.dir != RIGHT)
		{
			snake.dir = LEFT;
		}
		break;
	case 77:
	case 'd':
		if (snake.dir != LEFT)
		{
			snake.dir = RIGHT;
		}
		break;
	case ' ':
		MessageBox(NULL, "��ͣ", "snake", MB_OK);
	default:
		break;
	}
}

void creatFood()
{
	if (!food.flag)
	{
		//��ʼ��ʳ��
		do
		{
			food.x = rand() % (WIN_WIDTH / 10) * 10;
		} while (food.x < 20 || food.x > WIN_WIDTH - 20);
		do
		{
			food.y = rand() % (WIN_HEIGHT / 10) * 10;
		} while (food.y < 20 || food.y > WIN_HEIGHT - 20);
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.flag = true;
		COUNT = 0;
		
		do
		{
			bigFood.x = rand() % (WIN_WIDTH / 10) * 10;
			bigFood.y = rand() % (WIN_HEIGHT / 10) * 10;
		} while (bigFood.x == food.x && bigFood.y == food.y);
		bigFood.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		bigFood.flag = false;
		if (rand() % 5 < 1)
		{
			bigFood.flag = true;

		}
		
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

void eatBigFood()
{
	if (bigFood.flag == true && ((snake.coor[0].x == bigFood.x && snake.coor[0].y == bigFood.y) || (snake.coor[0].x == bigFood.x + 10 && snake.coor[0].y == bigFood.y + 10)))
	{
		bigFood.flag = false;
		snake.num += 3;
		for (int i = 2; i >= 0; i--)
		{
			snake.coor[snake.num - i].color = bigFood.color;
		}
		creatFood();
	}
}

void fail()
{
	int code = MessageBox(NULL, "�ò˰��ܵ�,������", "ʧ��", MB_YESNO);
	switch (code)
	{
	case IDYES:
		gameInit();
		break;
	case IDNO:
		exit(EXIT_SUCCESS);
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
	if (snake.num > 4)
	{
		for (int i = snake.num; i > 3; i--)
		{
			if (snake.coor[i].x == snake.coor[0].x && snake.coor[i].y == snake.coor[0].y)
			{
				fail();
			}
		}
	}
	
}
int main()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	setbkcolor(RGB(207, 214, 229));
	cleardevice();//ˢ�´���
	
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
		eatBigFood();
		
		if (bigFood.flag && COUNT++ == 100)
		{
			COUNT = 0;
			bigFood.flag = false;
		}
		gameFail();
		Sleep(100);
	}
	finally:system("exit");
	return 0;
}