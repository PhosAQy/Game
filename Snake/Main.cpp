#include <iostream>
#include <graphics.h>
#define MAX_SNAKE 500 //�ߵ�������
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
	cleardevice();//ˢ�´���
	
	gameInit();

	//���������ɫ
	setfillcolor(snake.coor[0].color);
	//������
	fillrectangle(snake.coor[0].x, snake.coor[0].y, 10, 10);
	//��Բ��
	fillcircle(20, 20, 10);
	system("pause");
	return 0;
}