#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "HWindow.h"
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void update();
	void draw();
private:
	sf::RenderWindow* window;
	Gamestate* gamestate;
};

