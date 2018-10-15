#pragma once
#include "LocalizedLabel.h"
class TextDisplay
{
public:
	TextDisplay();
	~TextDisplay();
	void Draw();
	void SetText(std::string text);
private:
	sf::RenderWindow* window;
	sf::RectangleShape* display;
	sf::Texture* displayBackground;
	std::vector<Label*> textLines;

};

