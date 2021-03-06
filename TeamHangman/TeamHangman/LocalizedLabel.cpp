#include "LocalizedLabel.h"

LocalizedLabel::LocalizedLabel() : Label()
{
	Initialize();
}

LocalizedLabel::LocalizedLabel(sf::Vector2f position, std::string key, int textSize, sf::Color textColor, bool isLocalized) : Label(position, key, textSize, textColor)
{
	Initialize();
	if (isLocalized)
	{
		this->isLocalized = true;
		this->key = key;
		this->text->setString(GetLocalizedString(key));
	}
}

LocalizedLabel::~LocalizedLabel()
{
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
			pickedLanguage = &Localization::english;
				break;
		case languages::Swedish:
			pickedLanguage = &Localization::swedish;
			break;
		default:
			pickedLanguage = &Localization::english;
			std::cout << "Could not find desired language, defaulting to english.\n";
			break;
		}
	}
	if (isLocalized)
	{
		text->setString(GetLocalizedString(key));
		OriginMiddle();
	}
}

void LocalizedLabel::Initialize()
{
	isInitialized = true;
	gamestate = Gamestate::Get();
	UpdateChosenLanguage();
}
