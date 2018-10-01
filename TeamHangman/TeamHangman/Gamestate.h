#pragma once
#include <iostream>
#include "GameData.h"
class Gamestate
{
public:
	~Gamestate();
	static Gamestate* Get();
	static void Clean();

	void PraiseErri(int iterations);
	enum State
	{
		Game,
		MainMenu,
		Options,
		Victory,
		Quit
	};
	State currentState;

	enum Languages
	{
		English,
		Swedish
	};
	Languages currentLanguage;

	GameData* playerData;
private:
	Gamestate();
	static Gamestate* Instance;
};

