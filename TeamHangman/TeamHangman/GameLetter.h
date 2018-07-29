#pragma once
#include "Label.h"
class GameLetter
{
public:
	//GameLetter(sf::Vector2f position, );
	GameLetter();
	~GameLetter();
private:
	sf::RenderWindow* window;
	Label* label;

};

