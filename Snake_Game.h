#pragma once
#include<GameMap.h>
#include<GameInput.h>
#include<GameDraw.h>
const int PROCESSING = 0;
const int WIN = 1;
const int LOSE = 2;

class Snake_Game
{
private:
	GameMap* game_map;//游戏地图
	GameInput* game_input;//输入
	GameDraw* game_draw;//绘图
	int speed;//游戏速度
public:
	Snake_Game(const int &l, const int &r,const int &GameSpeed);
	~Snake_Game();
	void GameStart();
	void GameRun();
	void GameEnd(const int & GameState);
	int GameLoop();//游戏是否结束
};

extern PlayerInput player_input;
extern GameAIInput AIinput;

