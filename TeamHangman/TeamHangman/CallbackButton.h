#pragma once
#include <iostream>
#include <functional>
#include "HWindow.h"
#include "Label.h"
#include "LocalizedLabel.h"
class CallbackButton
{
public:
	CallbackButton(std::function<void(std::string)> callback, std::string callbackString, std::string buttonText, sf::Vector2f position, bool isLocalized);
	CallbackButton();
	~CallbackButton();
	void update();
	void draw();
	void activate();
	void UpdateChosenLanguage();
	void OriginMiddle();
	void SetOrigin(sf::Vector2f modifier);
private:
	std::string callbackParameter;
	std::function<void(std::string)> callback;
	sf::RenderWindow* window;
	bool isPressed = false;
	LocalizedLabel* label;
	bool pressedOutside = false;
};

