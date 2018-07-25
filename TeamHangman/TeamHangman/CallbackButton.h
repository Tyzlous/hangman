#pragma once
#include <iostream>
#include <functional>
#include "HWindow.h"
#include "Label.h"
class CallbackButton
{
public:
	CallbackButton(std::function<void(std::string)> callback, std::string callbackString, std::string buttonText, sf::Vector2f position);
	CallbackButton();
	~CallbackButton();
	void update();
	void draw();
	void activate();
private:
	std::string callbackParameter;
	std::function<void(std::string)> callback;
	sf::RenderWindow* window;
	bool isPressed = false;
	Label* label;
};

