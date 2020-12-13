#include <iostream>
#include <time.h>
#include <iomanip>
#include <graphics.h>
#include <string>
#include <Windows.h>

#define MINE_NUM 150//雷的数量
#define ROW 30   //行
#define COL 30   //列
#define GRID_SIZE 17 //格子宽度
using namespace std;

int mine[COL][ROW];

IMAGE img[17];
//加载图片
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
	//随机生成一些雷  -1
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

	//雷周围的表格加一
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
	//加密
	for (int i = 0; i < COL; i++)
	{
		for (int k = 0; k < ROW; k++)
		{
			mine[i][k] += 20;
		}
	}
	gameDraw();

}

//界面绘制
void gameDraw()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			if (mine[i][j] == -1)
			{
				//贴图
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
		int error = MessageBox(NULL, "点雷了弟弟", "失败", MB_RETRYCANCEL);
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
//鼠标操作
void mouseEvent()
{
	while(1)
	{
		win = true;
		//判断有没有鼠标消息
		if (MouseHit())
		{
			//保存鼠标消息
			msg = GetMouseMsg();

			int openCol = msg.y / GRID_SIZE;
			int openRow = msg.x / GRID_SIZE;
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:        //左键打开

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

			case WM_RBUTTONDOWN:        //右键插旗
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
			int win = MessageBox(NULL, "强啊！", "胜利", MB_RETRYCANCEL);
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