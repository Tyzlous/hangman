#pragma once
#include "Label.h"
class GameLetter
{
public:
	GameLetter(sf::Vector2f position, std::string letter, int textSize, sf::Color textColor);
	GameLetter();
	~GameLetter();
	void Update();
	void Draw();
	void CompareToMyLetter(std::string letter);
	void OriginMiddle();
	bool beenFound();
private:
	sf::RenderWindow* window;
	Label* label;
	sf::RectangleShape* bottomLine;
	bool isFound = false;
	std::string myLetter;
};

