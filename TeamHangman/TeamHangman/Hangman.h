#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "HWindow.h"
#include "Gamestate.h"
#include "MainMenu.h"
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
};

