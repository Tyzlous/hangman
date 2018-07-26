#pragma once
#include "Label.h"
#include <unordered_map>
#include "Gamestate.h"
class LocalizedLabel : public Label
{
	typedef std::unordered_map<std::string, std::string> dictionary;
public:
	LocalizedLabel();
	LocalizedLabel(sf::Vector2f position, std::string text, int textSize, sf::Color textColor);
	~LocalizedLabel();

private:
	dictionary* english = nullptr;
	dictionary* swedish = nullptr;
	dictionary* pickedLanguage = nullptr;
	Gamestate* gamestate = nullptr;

	void InitializeLanguages();
	bool isInitialized = false;
	std::string GetLocalizedString(std::string key);
	void UpdateChosenLanguage();
	void Initialize();
};

