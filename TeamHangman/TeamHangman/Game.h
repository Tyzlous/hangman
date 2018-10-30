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
	bool GameWasWon();

private:
	const std::string PICTURE_PATH = "resources/pictures/hangman";
	const std::string BACKGROUND_IMAGE_PATH = "resources/mainMenuBackground.png";
	const std::string TITLE_IMAGE_PATH = "resources/title.png";
	sf::RenderWindow* window;
	Gamestate* gamestate;
	dictionary* pickedLanguage;
	std::vector<CallbackButton*> gameButtons;
	std::vector<std::string> words;
	std::vector<GameLetter*> gameLetters;
	std::vector<sf::Texture*> hangmanTextures;
	sf::RectangleShape* hangManRect;
	sf::Texture* backgroundTexture;
	sf::RectangleShape* backgroundImage;
	sf::Texture* titleTexture;
	sf::RectangleShape* titleImage;
	HangmanSoundManager* soundManager;
	int correctLetters = 0;
	unsigned int wrongGuesses = 0;
	void OnLetterPressed(std::string letter, CallbackButton* buttonPressed);
	void InitializeState();
	void KeyboardInit();
	void WordVectorInit();
	void LettersVectorInit();
	void EndGame();
	void InitializeTextures();
	bool startupComplete = false;
};

