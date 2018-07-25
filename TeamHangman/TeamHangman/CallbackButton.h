#pragma once
#include <iostream>
#include <functional>
#include "HWindow.h"
class CallbackButton
{
public:
	CallbackButton(std::function<void(std::string)> callback, std::string string);
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

