#pragma once
#include "LocalizedLabel.h"
#include "CallbackButton.h"
class Slider
{
public:
	Slider(sf::Vector2f position, float width, std::string textKey, std::function<void(float value)> callback, bool isLocalized);
	~Slider();
	void Update();
	void Draw();
private:
	sf::RenderWindow* window;
	sf::RectangleShape* line;
	sf::RectangleShape* slider;
	float lineStart, sliderPos, lineEnd, value;
	std::function<void(float value)> callback;
	bool isLocalized;
	bool beingDragged;
	void Init(sf::Vector2f position, float width, std::string textKey);
	void UpdatePosition();
	void Callback();
};

