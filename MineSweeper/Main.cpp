#include <iostream>
#include <time.h>
#include <iomanip>
#include <graphics.h>
#include <string>
#include <Windows.h>

#define MINE_NUM 150//�׵�����
#define ROW 30   //��
#define COL 30   //��
#define GRID_SIZE 17 //���ӿ��
using namespace std;

int mine[COL][ROW];

IMAGE img[17];
//����ͼƬ
string fileName;
bool hasBegin;
bool win;
MOUSEMSG msg;
void gameDraw();
void gameStart();
void gameInit()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			mine[i][j] = 0;
		}
	}
	srand(time(NULL));
	//�������һЩ��  -1
	for (int i = 0; i < MINE_NUM;)
	{

		int row = rand() % ROW;
		int col = rand() % COL;
		if (col >= 0 && col < COL && row >= 0 && row < ROW && mine[col][row] != -1)
		{
			mine[col][row] = -1;
			i++;
		}
	}

	//����Χ�ı���һ
	for (int i = 0; i < COL; i++)
	{
		for (int k = 0; k < ROW; k++)
		{
			if (mine[i][k] == -1)
			{
				for (int r = i - 1; r <= i + 1; r++)
				{
					for (int c = k - 1; c <= k + 1; c++)
					{
						if (r >= 0 && r < COL && c >= 0 && c < ROW && mine[r][c] != -1)
						{
							mine[r][c]++;
						}
					}
				}
			}
		}
	}
	//����
	for (int i = 0; i < COL; i++)
	{
		for (int k = 0; k < ROW; k++)
		{
			mine[i][k] += 20;
		}
	}
	gameDraw();

}

//�������
void gameDraw()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			if (mine[i][j] == -1)
			{
				//��ͼ
				putimage(GRID_SIZE * j, GRID_SIZE * i, &img[9]);
			}
			else if (mine[i][j] >= 0 && mine[i][j] <=8)
			{
				putimage(GRID_SIZE * j, GRID_SIZE * i, &img[mine[i][j]]);
			}
			else if (mine[i][j] >= 19 && mine[i][j] <= 28)
			{
				putimage(GRID_SIZE * j, GRID_SIZE * i, &img[10]);
			}
			else if (mine[i][j] > 28)
			{
				putimage(GRID_SIZE * j, GRID_SIZE * i, &img[11]);
			}
		}
	}
}

void fail(int openCol, int openRow)
{
	if (mine[openCol][openRow] == -1)
	{
		int error = MessageBox(NULL, "�����˵ܵ�", "ʧ��", MB_RETRYCANCEL);
		if (error == 4)
		{
			gameInit();
			gameDraw();
		}
		else if (error == 2)
		{
			mine[openCol][openRow] += 20;
			gameDraw();
		}
	}
}
void openBlank(int openCol, int openRow)
{
	if (mine[openCol][openRow] == 0)
	{
		for (int r = openCol - 1; r <= openCol + 1; r++)
		{
			for (int c = openRow - 1; c <= openRow + 1; c++)
			{
				if (r >= 0 && r < COL && c >= 0 && c < ROW && mine[r][c] > 19)
				{
					mine[r][c] -= 20;
					
					openBlank(r, c);
				}
			}
		}
	}
}

void instantOpen(int openCol, int openRow)
{
	if (mine[openCol][openRow] > 0 && mine[openCol][openRow] < 9)
	{
		int count = 0;
		for (int r = openCol - 1; r <= openCol + 1; r++)
		{
			for (int c = openRow - 1; c <= openRow + 1; c++)
			{
				if (r >= 0 && r < COL && c >= 0 && c < ROW && mine[r][c] > 28)
				{
					count++;
				}
			}
		}
		if (count == mine[openCol][openRow])
		{

			for (int r = openCol - 1; r <= openCol + 1; r++)
			{
				for (int c = openRow - 1; c <= openRow + 1; c++)
				{
					if (r >= 0 && r < COL && c >= 0 && c < ROW && mine[r][c] <= 28 && mine[r][c] >= 19)
					{
						mine[r][c] -= 20;
						if (mine[r][c] == -1)
						{
							gameDraw();
							fail(r, c);
							goto end;

						}
						openBlank(r, c);
					}
				}

			}
		end:;
			gameDraw();
		}
	}
}
//������
void mouseEvent()
{
	while(1)
	{
		win = true;
		//�ж���û�������Ϣ
		if (MouseHit())
		{
			//���������Ϣ
			msg = GetMouseMsg();

			int openCol = msg.y / GRID_SIZE;
			int openRow = msg.x / GRID_SIZE;
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:        //�����

				if (mine[openCol][openRow] >= 19)
				{
					
					mine[openCol][openRow] -= 20;
					gameDraw();
					fail(openCol, openRow);
					
				}
				if (mine[openCol][openRow] == 0)
				{
					openBlank(openCol, openRow);
					gameDraw();
				}
				
				if (GetMouseMsg().uMsg == WM_RBUTTONDOWN)
				{
					instantOpen(openCol, openRow);
				}
				break;

			case WM_RBUTTONDOWN:        //�Ҽ�����
				if (mine[openCol][openRow] >= 19 && mine[openCol][openRow] <= 28)
				{
					mine[openCol][openRow] += 20;
					gameDraw();
				}

				if (GetMouseMsg().uMsg == WM_LBUTTONDOWN)
				{
					instantOpen(openCol, openRow);
				}
				break;

		
			default:
				break;
			}
			

		}
		for (int i = 0; i < COL; i++)
		{
			for (int k = 0; k < ROW; k++)
			{
				if (mine[i][k] > 19 && mine[i][k] < 28)
				{
					win = false;
				}
			}
		}
		
		if (win)
		{
			int win = MessageBox(NULL, "ǿ����", "ʤ��", MB_RETRYCANCEL);
			if (win == 4)
			{
				gameInit();
				gameDraw();
			}
			else if (win == 2)
			{
				gameDraw();
			}
		}
		
	}
	
}

void gameStart()
{
	for (int i = 0; i < 17; i++)
	{
		fileName = "./resources/" + to_string(i) + ".gif";
		loadimage(&img[i], fileName.c_str());
	}
	gameInit();
	
	mouseEvent();
}
void show()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			cout << setw(3) << setfill(' ') << mine[i][j];
		}
		cout << endl;
	}
}

int main()
{
	
	initgraph(ROW * GRID_SIZE, COL * GRID_SIZE);

	gameStart();

	while (1);
	return 0;
}