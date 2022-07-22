#include "GameMap.h"
#include<iostream>
GameMap::GameMap(const int &l,const int &w) :width(w), length(l)
{
	G = new short* [length];
	for (int i = 0; i < length; i++)G[i] = new short[width];//动态开辟二维数组

	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			G[i][j] = GAP;
	Snake.push_back(std::make_pair(l>>1,w>>1));//在地图中心生成初始的蛇
	G[Snake[0].first][Snake[0].second] = SNAKE_BODY;
	FoodUpdate();
	istherefood = true;
}

GameMap::~GameMap()
{
	for (int i = 0; i < length; i++)delete[] G[i];
	delete G;
}

bool GameMap::MapUpdate(const char &direction)
{
	//删除蛇尾，插入新的蛇头
	std::pair<int, int> SnakeHead = Snake[0], SnakeTail = Snake.back();
	Snake.pop_back();
	//进行蛇身的更新
	//std::cout << direction << std::endl;
	switch (direction)
	{
	case 'w':
		SnakeHead.first--; break;
	case 'd':
		SnakeHead.second++; break;
	case 's':
		SnakeHead.first++; break;
	case 'a':
		SnakeHead.second--; break;
	}
	if (SnakeHead.first < 0 || SnakeHead.first >= length || SnakeHead.second<0 || SnakeHead.second>=width)//判断是否出界
		return false;
	if (G[SnakeHead.first][SnakeHead.second] == SNAKE_BODY)return false;//吃到蛇身了
	G[SnakeTail.first][SnakeTail.second] = GAP;
	if (G[SnakeHead.first][SnakeHead.second] == FOOD)
	{
		Snake.push_back(SnakeTail);
		G[SnakeTail.first][SnakeTail.second] = SNAKE_BODY;
		istherefood = false;
	}
	G[SnakeHead.first][SnakeHead.second] = SNAKE_BODY;

	Snake.insert(Snake.begin(), SnakeHead);//新蛇头加入到Snake中
	return true;
}


void GameMap::FoodUpdate()
{
	std::vector<std::pair<int, int> > FoodAvailable;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (G[i][j] == GAP)FoodAvailable.push_back(std::make_pair(i,j));
	if (FoodAvailable.size() == 0)return;
	int index = GetRandomNumber(0, FoodAvailable.size() - 1);
	G[FoodAvailable[index].first][FoodAvailable[index].second] = FOOD;
	istherefood = true;
}

bool GameMap::FoodUpdateAvailable()
{
	std::vector<std::pair<int, int> > FoodAvailable;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (G[i][j] == GAP)FoodAvailable.push_back(std::make_pair(i, j));
	if (FoodAvailable.size() == 0)return false;
	else return true;
}

int GameMap::GetRandomNumber(const int &l, const int &r)
{
	srand(time(0));
	int num = rand();
	return l + 1.0*num / RAND_MAX * (r - l);
}

bool GameMap::IsThereFood()
{
	return istherefood;
}