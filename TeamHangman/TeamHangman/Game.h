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
	void InitializeState();
	void KeyboardInit();
	void WordVectorInit();
	void Update();
	void Draw();
	void UpdateChosenLanguage();
	std::string GetLocalizedString(std::string key);
	std::string GetRandomLine();
	void print(std::string string);

private:
	sf::RenderWindow* window;
	Gamestate* gamestate;
	dictionary* pickedLanguage;
	std::vector<CallbackButton*> gameButtons;
	std::vector<std::string> words;

	void OnLetterPressed(std::string letter);
};

