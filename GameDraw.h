#pragma once
#include<GameMap.h>
#include<graphics.h>
const int SideLength = 50;//一个格子构成的像素点边长
class GameDraw
{
private:
	int length, width;//实际屏幕长度和宽度
public:
	GameDraw(int l,int w);
	void init(GameMap &game_map);//初始化窗口
	void draw(GameMap &game_map);//绘图
	~GameDraw();
	void GameWin();//游戏胜利
	void GameLose();//游戏失败
};

