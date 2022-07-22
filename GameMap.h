#pragma once
#include<vector>
#include<map>
#include<cstdlib>
#include<ctime>
const short GAP = 0;
const short SNAKE_BODY = 1;
const short FOOD = 2;
class GameMap
{
	friend class GameDraw;
private:
	short** G;//用一个二维地图存储地图
	//其中0表示空白，1表示蛇的身体，2表示食物

	int width, length; //地图的长宽
	std::vector<std::pair<int, int> > Snake;//存储蛇的身体的位置
	std::pair<int, int> food;//食物的位置

	int GetRandomNumber(const int &l, const int &r);//获取[l,r]的随机数
	bool istherefood;

public:
	GameMap(const int &l , const int &w );
	~GameMap();
	bool MapUpdate(const char & direction);		//如果更新后游戏是否结束
	void FoodUpdate();//更新食物
	bool FoodUpdateAvailable();
	bool IsThereFood();
};

