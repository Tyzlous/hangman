#pragma once
#include "Label.h"
#include "Gamestate.h"
#include "Localization.h"
class LocalizedLabel : public Label
{
public:
	LocalizedLabel();
	LocalizedLabel(sf::Vector2f position, std::string key, int textSize, sf::Color textColor, bool isLocalized);
	~LocalizedLabel();
	void UpdateChosenLanguage();

private:
	dictionary* pickedLanguage = nullptr;
	Gamestate* gamestate = nullptr;
	std::string key;

	bool isLocalized = false;
	bool isInitialized = false;
	std::string GetLocalizedString(std::string key);
	void Initialize();
};

