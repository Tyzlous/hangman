#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "HWindow.h"
#include "CallbackButton.h"
class Options
{
public:
	Options();
	~Options();
	void Update();
	void Draw();
private:
	sf::RenderWindow* window;
};

