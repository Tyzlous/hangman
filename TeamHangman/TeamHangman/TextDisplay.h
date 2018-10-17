#pragma once
#include "LocalizedLabel.h"
class TextDisplay
{
public:
	TextDisplay(sf::Vector2f position, sf::Vector2f size, std::string title);
	TextDisplay();
	~TextDisplay();
	void Draw();
	void SetText(std::string newString);
	void AddText(std::string stringToAdd);
	void NewLineOfText(std::string text);
	void SetSize(sf::Vector2f newSize);
	void SetTitle(std::string newString);
private:
	void InitializeDisplay(sf::Vector2f position, sf::Vector2f size, std::string title);
	void ProcessTextToLines();
	sf::RenderWindow* window;
	sf::RectangleShape* display;
	const std::string TEXTURE_DIR = "resources/whiteBlackGradient.jpg";
	const unsigned int titleFontSize = 30;
	const unsigned int contentFontSize = 24;
	sf::Texture* displayTexture;
	std::string contentText;
	Label* titleText;
	Label* contentLabel;
};

