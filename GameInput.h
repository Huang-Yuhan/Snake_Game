#pragma once

#include<GameMap.h>

class GameInput
{
public:
	virtual char GetInput(const int &speed)=0;
};

class PlayerInput :public GameInput
{
private:
	bool IsContrary(char a, char b);
public:
	char LastInput;
	char GetInput(const int &speed);
	PlayerInput()
	{
		LastInput = 0;
	}
};

class GameAIInput :public GameInput
{
private:
	int length, width;
	GameMap* game_map;
	GameMap* virtual_map;
	int** dis;
	char JudgeDirection(std::pair<int, int>, std::pair<int, int>);
	void PrintVirtualMap();
	void PrintMap();
public:
	void LinkMap(GameMap* Map);
	char GetInput(const int &speed);
};

