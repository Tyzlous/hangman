#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include"HWindow.h"
#include"LocalizedLabel.h"
class TextBox
{
public:
	TextBox();
	TextBox(sf::Vector2f position, unsigned int size, unsigned int maxLetterCount, std::string key);
	~TextBox();
	void Update();
	void Draw();
	void SetString(std::string newString);
	void UpdateString(char charToAdd);
	void PopBackString();
	void SetPosition(sf::Vector2f value);
	sf::Vector2f GetPosition();
	bool IsActive();
	bool IsNotEmpty();
	std::string GetConfirmedString();
	std::string GetLabelString();
	void ConfirmCurrentString();
private:
	sf::RenderWindow* window;
	sf::RectangleShape* box;
	sf::Text* text;
	sf::Font* font;
	std::string confirmedString;
	LocalizedLabel* title;
	bool isActive;
	unsigned int maxLetterCount;
	void TextInit(sf::Vector2f position, unsigned int size);
	void BoxInit(sf::Vector2f position, unsigned int size);
	void SetTitle(std::string key, unsigned int size);
	void Centralize();
};

