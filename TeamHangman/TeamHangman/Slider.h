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
	void SetLineTexture(std::string texturePath);
	void SetHandleTexture(std::string texturePath);
private:
	sf::RenderWindow* window;
	sf::RectangleShape* line;
	sf::RectangleShape* slider;
	sf::Texture* lineTexture;
	sf::Texture* handleTexture;
	LocalizedLabel* label;
	float lineRectLeft, sliderPosX, lineWidth, value;
	std::function<void(float value)> callback;
	bool isLocalized;
	bool beingDragged;
	void Init(sf::Vector2f position, float width, std::string textKey);
	void UpdatePosition();
	void Callback();
};

