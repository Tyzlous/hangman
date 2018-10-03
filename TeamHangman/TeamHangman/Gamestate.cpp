#include "Gamestate.h"

Gamestate* Gamestate::Instance = nullptr;

Gamestate::Gamestate()
{
	currentState = State::MainMenu;
	currentLanguage = Languages::English;
	playerData = new GameData("Plebian");
}


Gamestate::~Gamestate()
{
	if (playerData != nullptr)
	{
		delete playerData;
	}
}

void Gamestate::PraiseErri(int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		std::cout << "Erri is the greatest!\n";
	}
}

Gamestate * Gamestate::Get()
{
	if (Instance == nullptr)
	{
		Instance = new Gamestate();
	}
	return Instance;
}

void Gamestate::Clean()
{
	if (Instance != nullptr)
	{
		delete Instance;
	}
}
