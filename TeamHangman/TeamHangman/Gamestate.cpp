#include "Gamestate.h"

Gamestate* Gamestate::Instance = nullptr;

Gamestate::Gamestate()
{
	currentState = State::MainMenu;
	currentLanguage = Languages::English;
	playerData = new GameData();
}


Gamestate::~Gamestate()
{
	if (playerData != nullptr)
	{
		delete playerData;
	}
}

std::string Gamestate::GetLocalizedString(std::string KEY)
{
	std::string localizedString = "NAN";
	std::unordered_map<std::string, std::string>::const_iterator value;
	switch (currentLanguage)
	{
	case English:
		value = Localization::english.find(KEY);
		localizedString = value->second;
		break;
	case Swedish:
		value = Localization::swedish.find(KEY);
		localizedString = value->second;
		break;
	default:
		value = Localization::english.find(KEY);
		localizedString = value->second;
		std::cout << "Could not find desired language, defaulting to english.\n";
		break;
	}
	return localizedString;
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