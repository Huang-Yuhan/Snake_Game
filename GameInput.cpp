#include "GameInput.h"
#include<conio.h>
#include<time.h>
PlayerInput player_input;
GameAIInput AIinput;
char PlayerInput::GetInput(const int &speed)
{
	char c = LastInput;
	clock_t pre_t = clock();
	while (clock() - pre_t <= speed)
	{
		if (_kbhit()) { c = _getch();  }
	}
	switch (c)
	{
	case 'w':
	case 72:
	case 'W':return LastInput='w';
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

char GameAIInput::GetInput(const int &speed)
{
	return '0';
}
