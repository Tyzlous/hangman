#pragma once
#include <vector>
#include <fstream>
#include "Gamestate.h"
#include "CallbackButton.h"
#include "GameLetter.h"
class Game
{
public:
	Game();
	~Game();
	void InitializeState();
	void KeyboardInit();
	void WordVectorInit();
	void LettersVectorInit();
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
	std::vector<GameLetter*> gameLetters;

	void OnLetterPressed(std::string letter);
};

