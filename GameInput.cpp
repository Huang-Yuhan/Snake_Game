#include "GameInput.h"
#include<conio.h>
#include<time.h>
#include<queue>
#include<Windows.h>
#include<iostream>
#include<iomanip>
PlayerInput player_input;
GameAIInput AIinput;

bool PlayerInput::IsContrary(char dir1, char dir2)
{
	switch (dir1)
	{
	case 'w':
	case 72:
	case 'W':return dir2 == 's';
	case 's':
	case 80:
	case 'S':return dir2 == 'w';
	case 'a':
	case 75:
	case 'A':return dir2 == 'd';
	case 'd':
	case 77:
	case 'D':return dir2 == 'a';
	}
}

char PlayerInput::GetInput(const int &speed)
{
	char c = LastInput;
	clock_t pre_t = clock();
	while (clock() - pre_t <= speed)
	{
		if (_kbhit()) 
		{ 
			c = _getch(); 
			if (IsContrary(c, LastInput))c = LastInput;  
		}
	}
	if (c == 0)c = 'w';
	switch (c)
	{
	case 'w':
	case 72:
	case 'W':return LastInput=	'w';
	case 's':
	case 80:
	case 'S':return LastInput = 's';
	case 'a':
	case 75:
	case 'A':return LastInput = 'a';
	case 'd':
	case 77:
	case 'D':return LastInput = 'd';
	default:return 0; break;
	}
}

void GameAIInput::LinkMap(GameMap* Map)
{
	game_map = Map;
	length = game_map->length;
	width = game_map->width;
	dis = new int* [length];
	for (int i = 0; i < length; i++)dis[i] = new int[width];
}

char GameAIInput::JudgeDirection(std::pair<int, int> obj1, std::pair<int, int> obj2)//判断obj2在obj1的哪个方向
{
	if (obj1.first == obj2.first)
	{
		if (obj2.second == obj1.second + 1)return 'd';
		if (obj2.second == obj1.second - 1) return 'a';
	}
	if (obj1.second == obj2.second)
	{
		if (obj2.first == obj1.first + 1)return 's';
		if (obj2.first == obj1.first - 1)return 'w';
	}
	return 0;
}

void GameAIInput::PrintVirtualMap()
{
	std::cout << "\n\nvirtual_map:\n";
	for(int i=0;i<length;i++)
		for (int j = 0; j < width; j++)
		{
			if (virtual_map->G[i][j] == SNAKE_BODY)
			{
				if (std::make_pair(i, j) == virtual_map->Snake[0])std::cout << " h";
				else if (std::make_pair(i, j) == virtual_map->Snake.back())std::cout << " t";
				else std::cout << " #";
			}
			if (virtual_map->G[i][j] == FOOD)std::cout << " $";
			if (virtual_map->G[i][j] == GAP)std::cout << "  ";
			if (j == width - 1)std::cout << '\n';
		}

}

void GameAIInput::PrintMap()
{
	std::cout << "\n\nmap:\n";
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
		{
			if (game_map->G[i][j] == SNAKE_BODY)
			{
				if (std::make_pair(i, j) == game_map->Snake[0])std::cout << " h";
				else if (std::make_pair(i, j) == game_map->Snake.back())std::cout << " t";
				else std::cout << " #";
			}
			if (game_map->G[i][j] == FOOD)std::cout << " $";
			if (game_map->G[i][j] == GAP)std::cout << "  ";
			if (j == width - 1)std::cout << '\n';
		}

}

char GameAIInput::GetInput(const int &speed)
{
	clock_t pre_t = clock();
	/*策略很简单
	首先去找是否可以找到食物。
	if 沿着最短路吃掉食物后可以找到尾巴->移动
	else 
	{
		随机移动（移动后满足要找到尾巴并且离食物距离最远）
	}
	
	
	
	
	
	*/
	//PrintMap();
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			dis[i][j] = -1;
	std::queue<std::pair<int, int> > q;
	std::pair<int, int> node = game_map->food;
	dis[node.first][node.second] = 0;
	q.push(node);
	/*预处理dis数组*/
	int dx, dy;
	int DX[] = {0,0,1,-1};
	int DY[] = {1,-1,0,0};
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			dx = node.first + DX[i];
			dy = node.second + DY[i];
			if(game_map->Snake.at(0).first==dx&&game_map->Snake.at(0).second==dy)
			if (std::make_pair(dx,dy) == game_map->Snake.at(0))
			{
				if(dis[dx][dy]==-1||dis[dx][dy] > dis[node.first][node.second] + 1)
					dis[dx][dy] = dis[node.first][node.second] + 1;
			}
			if (0 <= dx && dx < length && 0 <= dy && dy < width && game_map->G[dx][dy] != SNAKE_BODY)//未出界且不是蛇身
			{
				if (dis[dx][dy] == -1)
				{
					dis[dx][dy] = dis[node.first][node.second] + 1;
					q.push(std::make_pair(dx, dy));

				}
				else
				{
					if (dis[dx][dy] > dis[node.first][node.second] + 1)
					{
						dis[dx][dy] = dis[node.first][node.second] + 1;
						q.push(std::make_pair(dx, dy));

					}
				}
			}
		}
	}
	/*std::cout << "dis:\n";
	for (int i = 0; i < length; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < width; j++)
		{
			std::cout <<std::setw(2)<< dis[i][j];
		}
	}
	std::cout << "\n";*/
	virtual_map = new GameMap(*game_map);
	//是否可以吃到食物（找到蛇头到食物的最短路径）
	std::pair<int, int> snake_head = virtual_map->Snake.at(0), move_target = std::make_pair(-1, -1), snake_tail=virtual_map->Snake.back();
	for (int i = 0; i < 4; i++)
	{
		dx = snake_head.first + DX[i];
		dy = snake_head.second + DY[i];
		if (0 <= dx && dx < length && 0 <= dy && dy < width && game_map->G[dx][dy]!=SNAKE_BODY&&dis[dx][dy]!=-1)
		{
			if (move_target.first == -1)
			{
				move_target.first = dx;
				move_target.second = dy;
			}
			else
			{
				if (dis[move_target.first][move_target.second] > dis[dx][dy])
				{
					move_target.first = dx;
					move_target.second = dy;
				}
			}
		}
	}
	bool CanFindFoodOrNot;
	char ans;
	if (dis[snake_head.first][snake_head.second] == -1)CanFindFoodOrNot = false;
	else
	{
		CanFindFoodOrNot = true;
		//如果找到食物：用虚拟蛇去吃，如果吃食物后还能找到蛇尾，那么就吃，否则追蛇尾
		ans = JudgeDirection(snake_head, move_target);
		int NowDis;
		while (dis[move_target.first][move_target.second] != 0)
		{
			virtual_map->MapUpdate(JudgeDirection(snake_head, move_target));
			snake_head = move_target;
			NowDis = dis[snake_head.first][snake_head.second];
			for (int i = 0; i < 4; i++)
			{
				dx = snake_head.first + DX[i];
				dy = snake_head.second + DY[i];
				if (0 <= dx && dx < length && 0 <= dy && dy < width && dis[dx][dy] == NowDis - 1)
				{
					move_target.first = dx;
					move_target.second = dy;
				}
			}
		}
		virtual_map->MapUpdate(JudgeDirection(snake_head, move_target));
		snake_head = move_target;
		//PrintVirtualMap();
		snake_tail = virtual_map->Snake.back();
		for (int i = 0; i < length; i++)
			for (int j = 0; j < width; j++)
				dis[i][j] = -1;
		dis[snake_head.first][snake_head.second] = 0;
		q.push(snake_head);
		while (!q.empty())
		{
			node = q.front();
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				dx = node.first + DX[i];
				dy = node.second + DY[i];
				if (std::make_pair(dx, dy) == snake_tail)
					if(dis[dx][dy]==-1|| dis[dx][dy] > dis[node.first][node.second] + 1)
						dis[dx][dy] = dis[node.first][node.second] + 1;
				if (0 <= dx && dx < length && 0 <= dy && dy < width && virtual_map->G[dx][dy] != SNAKE_BODY)//未出界且不是蛇身
				{
					if (dis[dx][dy] == -1)
					{
						dis[dx][dy] = dis[node.first][node.second] + 1;
						q.push(std::make_pair(dx, dy));

					}
					else
					{
						if (dis[dx][dy] > dis[node.first][node.second] + 1)
						{
							dis[dx][dy] = dis[node.first][node.second] + 1;
							q.push(std::make_pair(dx, dy));
						}
					}
				}
			}
		}
		if (dis[snake_tail.first][snake_tail.second]!=-1&&(JudgeDirection(snake_head,snake_tail)==false||virtual_map->Snake.size()==2))
		{
			clock_t t = clock();
			if (t - pre_t < 100)Sleep(100 - t + pre_t);
			return ans;
		}
	}
	//如果蛇头找不到食物，就追蛇尾
	snake_tail = game_map->Snake.back();
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			dis[i][j] = -1;
	dis[snake_tail.first][snake_tail.second] = 0;
	q.push(snake_tail);
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			dx = node.first + DX[i];
			dy = node.second + DY[i];
			if (0 <= dx && dx < length && 0 <= dy && dy < width && game_map->G[dx][dy] != SNAKE_BODY)//未出界且不是蛇身
			{
				if (dis[dx][dy] == -1)
				{
					dis[dx][dy] = dis[node.first][node.second] + 1;
					q.push(std::make_pair(dx, dy));

				}
				else
				{
					if (dis[dx][dy] > dis[node.first][node.second] + 1)
					{
						dis[dx][dy] = dis[node.first][node.second] + 1;
						q.push(std::make_pair(dx, dy));
					}
				}
			}
		}
	}
	snake_head = game_map->Snake.at(0);
	move_target = snake_tail;
	for (int i = 0; i < 4; i++)
	{
		dx = snake_head.first + DX[i];
		dy = snake_head.second + DY[i];
		if (0 <= dx && dx < length && 0 <= dy && dy < width && game_map->G[dx][dy]!=SNAKE_BODY&&dis[dx][dy]!=-1)
		{
			if (dis[move_target.first][move_target.second] < dis[dx][dy])
			{
				move_target.first = dx;
				move_target.second = dy;
			}
		}
	}
	char FollowTail= JudgeDirection(snake_head, move_target);
	clock_t t = clock();
	if (t - pre_t < 100)Sleep(100 - t + pre_t);
	return FollowTail;
}
