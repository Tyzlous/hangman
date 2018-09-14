#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "HWindow.h"
#include "Gamestate.h"
#include "MainMenu.h"
#include "Game.h"
#include "HangmanSoundManager.h"
#include "Victory.h"
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
	HangmanSoundManager* soundManager;
	Victory* victory;
};

