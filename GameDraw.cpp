#include "GameDraw.h"
#include<conio.h>
GameDraw::GameDraw(int l, int w) :length(l* SideLength), width(w* SideLength)
{

}

void GameDraw::init(GameMap &game_map)
{
	initgraph(width, length);
	setfillcolor(WHITE);
	setbkcolor(BLACK);
	draw(game_map);
	LPCTSTR  GameStartOutput =_T("请按任意键开始游戏！");
	outtextxy(SideLength,SideLength,GameStartOutput);//显示按下任意键开始游戏
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
				left = j * SideLength;
				right = (j + 1) * SideLength;
				top = i * SideLength;
				bottom = top + SideLength;
				fillrectangle(left, top, right, bottom);
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
	cleardevice();
	LPCTSTR  GameEndOutput = _T("你获得胜利！(5s后自动退出)");
	outtextxy(length/2, width/2, GameEndOutput);//游戏胜利
	Sleep(5000);
}

void GameDraw::GameLose()
{
	cleardevice();
	LPCTSTR  GameEndOutput = _T("你失败了！(5s后自动退出)");
	outtextxy(length / 2, width / 2, GameEndOutput);//游戏失败
	Sleep(5000);
}