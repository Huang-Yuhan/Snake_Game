#include<Snake_Game.h>
#include<iostream>
#include<string>
int MapLength = 10, MapWidth = 10;//默认地图大小
int GameSpeed = 3;
void MapSizeSet()
{
	std::cout << "请设置地图长度:";
	std::cin >> MapLength;
	std::cout << "请设置地图宽度:";
	std::cin >> MapWidth;
}

int main()
{
	while(1)
	{
		std::cout << "<--------欢迎来到贪吃蛇------->\n";
		std::cout << "1.开始游戏\n";
		std::cout << "2.设置地图大小(默认为10*10)\n";
		std::cout << "3. 退出\n\n\n";
		std::cout << "4. 设置速度\n";

		std::cout << "请输入选项：";
		std::string PlayerInput;
		std::cin >> PlayerInput;
		if (PlayerInput.length() != 1)
		{
			std::cout << "输入不合法！\n";
			continue;
		}
		char PlayerChoice = PlayerInput[0];
		if (!isdigit(PlayerChoice))
		{
			std::cout << "输入不合法！\n";
			continue;
		}
		switch (PlayerChoice)
		{
			case '2':
			{
				MapSizeSet(); break; 
			}
			case '1': 
			{
				Snake_Game* GAME = new Snake_Game(MapLength, MapWidth,GameSpeed);
				GAME->GameRun();
				delete GAME; 
				break; 
			}
			case '3':
			{
				exit(0); 
			}
			case '4':
			{
				std::cout << "请选择速度等级(1,2,3)(数字越大速度越慢):";
				std::cin >> GameSpeed;
				break;
			}
			default: 
			{
				std::cout << "输入不合法！\n";
				continue; break;
			}
		}
	}
	return 0;
}