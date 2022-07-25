#include "GameDraw.h"
#include<conio.h>
GameDraw::GameDraw(int l, int w) :length(l* SideLength), width(w* SideLength)
{

}

void GameDraw::init(GameMap &game_map)
{
	initgraph(width, length, EW_SHOWCONSOLE);
	setfillcolor(WHITE);
	setbkcolor(BLACK);
	draw(game_map);
	LPCTSTR  GameStartOutput =_T("请按任意键开始游戏！");
	outtextxy(1,width/2,GameStartOutput);//显示按下任意键开始游戏
}

void GameDraw::draw(GameMap &game_map)
{
	cleardevice();
	int left, top, right, bottom;
	for(int i=0;i<game_map.length;i++)
		for (int j = 0; j < game_map.width; j++)
		{
			switch (game_map.G[i][j])
			{
			case SNAKE_BODY:
				left = j * SideLength+1;
				right = (j + 1) * SideLength-1;
				top = i * SideLength+1;
				bottom = top + SideLength-2;
				if (std::make_pair(i, j) == game_map.Snake[0])
				{
					setfillcolor(RED);
					fillrectangle(left, top, right, bottom);
					setfillcolor(WHITE);
				}
				else if(std::make_pair(i,j)==game_map.Snake.back())
				{
					setfillcolor(GREEN);
					fillrectangle(left, top, right, bottom);
					setfillcolor(WHITE);
				}
				else fillrectangle(left, top, right, bottom);
				break;
			case FOOD:
				left = j * SideLength;
				top = i * SideLength;
				fillcircle(left + SideLength / 2, top + SideLength / 2, SideLength / 2);
			default:break;
			}
			
		}
}

GameDraw::~GameDraw()
{
	closegraph();
}

void GameDraw::GameWin()
{
	LPCTSTR  GameEndOutput = _T("你获得胜利！(5s后自动退出)");
	outtextxy(1, width/2, GameEndOutput);//游戏胜利
	while (!_kbhit()) {}

	Sleep(5000);
}

void GameDraw::GameLose()
{
	LPCTSTR  GameEndOutput = _T("你失败了！(5s后自动退出)");
	outtextxy(1, width / 2, GameEndOutput);//游戏失败
	while (!_kbhit()) {}

	Sleep(5000);
}