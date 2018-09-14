#pragma once
#include <vector>
#include <fstream>
#include "Gamestate.h"
#include "CallbackButton.h"
#include "GameLetter.h"
#include "HangmanSoundManager.h"

class Game
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
	void UpdateChosenLanguage();
	void ResetGame();
	std::string GetLocalizedString(std::string key);
	std::string GetRandomLine();
	void print(std::string string);
	void SetSoundManager(HangmanSoundManager* soundManager);

private:
	sf::RenderWindow* window;
	Gamestate* gamestate;
	dictionary* pickedLanguage;
	std::vector<CallbackButton*> gameButtons;
	std::vector<std::string> words;
	std::vector<GameLetter*> gameLetters;
	HangmanSoundManager* soundManager;
	int correctLetters = 0;
	void OnLetterPressed(std::string letter, CallbackButton* buttonPressed);
	void InitializeState();
	void KeyboardInit();
	void WordVectorInit();
	void LettersVectorInit();
};

