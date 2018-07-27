#pragma once
#include <vector>
#include <fstream>
#include "Gamestate.h"
#include "CallbackButton.h"
class Game
{
public:
	Game();
	~Game();
	void Initialize();
	void KeyboardInit();
	void Update();
	void Draw();
	void UpdateChosenLanguage();
	std::string GetLocalizedString(std::string key);
private:
	sf::RenderWindow* window;
	Gamestate* gamestate;
	dictionary* pickedLanguage;
	std::vector<CallbackButton*> gameButtons;

	void OnLetterPressed(std::string letter);
};

