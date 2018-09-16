#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "HWindow.h"
#include "Gamestate.h"
#include "MainMenu.h"
#include "Game.h"
#include "HangmanSoundManager.h"
#include "Victory.h"
#include "GameData.h"
class Hangman
{
public:
	Hangman();
	~Hangman();
	void Start();
private:
	sf::RenderWindow* window;
	Gamestate* gamestate;
	MainMenu* mainMenu;
	Game* game;
	GameData* playerData;
	HangmanSoundManager* soundManager;
	Victory* victory;
	void GameDataEvent();
};

