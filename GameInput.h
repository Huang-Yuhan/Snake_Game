#pragma once

class GameInput
{
public:
	virtual char GetInput(const int &speed)=0;
};

class PlayerInput :public GameInput
{
public:
	char LastInput;
	char GetInput(const int &speed);
	PlayerInput()
	{
		LastInput = 'w';
	}
};

class GameAIInput :public GameInput
{
public:
	char GetInput(const int &speed);
};

