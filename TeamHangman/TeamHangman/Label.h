#pragma once
#include "HWindow.h"
#include <string>

class Label
{
public:
	Label();
	Label(sf::Vector2f position, std::string text, int textSize, sf::Color textColor);
	~Label();
	void Draw();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	void AddPosition(sf::Vector2f addPosition);
	sf::FloatRect GetGlobalBounds();
	bool Contains(sf::Vector2f point);
	void EnableDebugDraw(bool enable);
	void SetColor(sf::Color color);
	void Highlight(sf::Color color = sf::Color::Blue);
	void DeHighlight();

private:
	sf::RenderWindow* window = nullptr;
	sf::Text* text = nullptr;
	sf::Font* font;
	sf::Color baseColor, highlightColor;

	const std::string FONT_NAME = "gameFont.ttf";
	bool debugDrawEnabled = false;
	bool isHighlighted = false;

	void DrawDebug();

};

