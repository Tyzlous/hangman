#pragma once
#include <iostream>
#include "GameData.h"
#include <unordered_map>
#include "Localization.h"
class Gamestate
{
public:
	~Gamestate();
	static Gamestate* Get();
	static void Clean();

	std::string GetLocalizedString(std::string KEY);
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

