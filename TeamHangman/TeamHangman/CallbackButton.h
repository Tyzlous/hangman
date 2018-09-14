#pragma once
#include <iostream>
#include <functional>
#include "HWindow.h"
#include "Label.h"
#include "LocalizedLabel.h"
class CallbackButton
{
public:
	CallbackButton(std::function<void(std::string, CallbackButton*)> callback, std::string callbackString, std::string buttonText, sf::Vector2f position, bool isLocalized);
	CallbackButton();
	~CallbackButton();
	void update();
	void draw();
	void activate();
	void disable();
	void enable();
	void UpdateChosenLanguage();
	void OriginMiddle();
	void SetOrigin(sf::Vector2f modifier);
	void SetTexture(std::string texturePath);
	sf::Vector2f GetOrigin();

private:
	std::string callbackParameter;
	std::function<void(std::string, CallbackButton*)> callback;
	sf::RenderWindow* window;
	bool isPressed = false;
	LocalizedLabel* label;
	bool pressedOutside = false;
	bool enabled = true;
	sf::Texture* texture = nullptr;
	sf::RectangleShape* backgroundImage = nullptr;
};

