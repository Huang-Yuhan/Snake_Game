#include "Snake_Game.h"
#include<iostream>
#include<cstring>
#include<conio.h>
Snake_Game::Snake_Game(const int &l, const int &w,const int &GameSpeed)
{
	game_map = new GameMap(l, w);
	game_draw = new GameDraw(l, w);
	game_input = &player_input;
	switch (GameSpeed)
	{
	case 1: speed = 500; break;
	case 2:	speed = 750; break;
	case 3:	speed = 1000; break;
	}
}

Snake_Game::~Snake_Game()
{
	delete game_map;
	delete game_draw;
	game_input = nullptr;
}

void Snake_Game::GameStart()
{
	//询问是player还是AI模式
	//Gameinput指向不同对象（返回函数设置为虚函数）
	std::cout << "选择player还是由AI完成游戏？[p/a]:";
	char GameObjChoice;
	std::cin >> GameObjChoice;
	if (isupper(GameObjChoice))GameObjChoice = GameObjChoice - 'A' + 'a';//切换到小写。
	if (GameObjChoice!='p'&& GameObjChoice!='a')
	{
		std::cout << "输入无效！\n";
		return;
	}
	//Player
	if(GameObjChoice=='p')
	{
		game_input =  &player_input;
	}
	else
	{
		game_input = &AIinput;
	}	
	//开始绘图
	game_draw->init(*game_map);
	while (!_kbhit()) {}
	return;
}

void Snake_Game::GameEnd(const int & GameState)
{
	if (GameState == WIN)
	{
		//游戏胜利
		game_draw->GameWin();
	}
	else
	{
		//游戏失败
		game_draw->GameLose();
	}
}

int Snake_Game::GameLoop()
{
	char Input = game_input->GetInput(speed);
	if (game_map->MapUpdate(Input) == false)//如果蛇死掉
	{
		return LOSE;//游戏失败
	}
	else 
	{
		//游戏未结束
		if (game_map->IsThereFood() == false)//如果没食物
		{
			if (game_map->FoodUpdateAvailable() == false)//并且没空位更新食物
				return WIN;
			else game_map->FoodUpdate();
		}
		return PROCESSING;
	}
}

void Snake_Game::GameRun()
{
	GameStart();
	int GameState;
	while (1)
	{
		GameState = GameLoop();
		if (GameState != PROCESSING)break;
		//绘图
		game_draw->draw(*game_map);
	}
	GameEnd(GameState);
}

//用户未输入沿用上一次的输入
//绘图后按任意键开始游戏
//