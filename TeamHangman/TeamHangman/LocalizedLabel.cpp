#include "LocalizedLabel.h"

LocalizedLabel::LocalizedLabel()
{
	Initialize();
}

LocalizedLabel::LocalizedLabel(sf::Vector2f position, std::string text, int textSize, sf::Color textColor)
{
	Initialize();
	std::cout << GetLocalizedString("KEY_HELLO");
}


LocalizedLabel::~LocalizedLabel()
{
	if (isInitialized)
	{
		delete english;
		delete swedish;
	}
}

void LocalizedLabel::InitializeLanguages()
{

	english = new dictionary{
		{ "KEY_HELLO", "Hello" },
		{ "KEY_HANGMAN", "Hangman" },
		{ "KEY_START", "Start" },
		{ "KEY_QUIT", "Quit" },
		{ "KEY_YOU_LOSE", "You lose!" },
		{ "KEY_YOU_WIN", "You win!" }
	};

	swedish = new dictionary{
		{ "KEY_HELLO", "Hej" },
		{ "KEY_HANGMAN", "Hangman" },
		{ "KEY_START", "Start" },
		{ "KEY_QUIT", "Quit" },
		{ "KEY_YOU_LOSE", "You lose!" },
		{ "KEY_YOU_WIN", "You win!" }
	};
}

std::string LocalizedLabel::GetLocalizedString(std::string key)
{
	std::string localizedString = "NAN";

	if (pickedLanguage != nullptr)
	{
		dictionary::const_iterator value = pickedLanguage->find(key);

		//if we found a value
		if (value != pickedLanguage->end())
		{
			localizedString = value->second;
		}
	}

	return localizedString;
}

void LocalizedLabel::UpdateChosenLanguage()
{
	typedef Gamestate::Languages languages;
	if (gamestate != nullptr)
	{
		switch (gamestate->currentLanguage)
		{
		case languages::English:
			pickedLanguage = english;
				break;
		case languages::Swedish:
			pickedLanguage = swedish;
			break;
		default:
			pickedLanguage = english;
			std::cout << "Could not find desired language, defaulting to english.\n";
			break;
		}
	}
}

void LocalizedLabel::Initialize()
{
	isInitialized = true;
	gamestate = Gamestate::Get();
	InitializeLanguages();
	UpdateChosenLanguage();
}
