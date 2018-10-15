#pragma once
#include "LocalizedLabel.h"
class TextDisplay
{
public:
	TextDisplay(sf::Vector2f position, sf::Vector2f size, std::string title);
	TextDisplay();
	~TextDisplay();
	void Draw();
	void NewLineOfText(std::string text);
private:
	sf::RenderWindow* window;
	sf::RectangleShape* display;
	const std::string TEXTURE_DIR = "resources/whiteBlackGradient.jpg";
	sf::Texture* displayBackground;
	std::vector<Label*> textLines;
	Label* titleText;
	void InitializeDisplay(sf::Vector2f position, sf::Vector2f size, std::string title);
	void UpdateRect();
	
};

