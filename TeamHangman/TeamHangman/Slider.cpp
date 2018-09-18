#include "Slider.h"



Slider::Slider(sf::Vector2f position, float width, std::string textKey, std::function<void(float value)> callback, bool isLocalized)
{
	window = HWindow::GetWindow();
	Init(position, width, textKey);
	this->callback = callback;
	this->isLocalized = isLocalized;

}


Slider::~Slider()
{
	delete line;
	delete slider;
}

void Slider::Update()
{
}

void Slider::Draw()
{
}

void Slider::Init(sf::Vector2f position, float width, std::string textKey)
{
	line = new sf::RectangleShape(sf::Vector2f(width, 10.0f));
	sf::FloatRect rect = line->getLocalBounds();
	line->setOrigin(rect.left + rect.width * 0.5f, rect.top + rect.height * 0.5f);

	slider = new sf::RectangleShape(sf::Vector2f(line->getSize().x * 0.05f, line->getSize().x * 0.05f));
	rect = slider->getLocalBounds();
	slider->setOrigin(rect.left + rect.width * 0.5f, rect.top + rect.height * 0.5f);

	line->setFillColor(sf::Color::Green);
	slider->setFillColor(sf::Color::Green);
}
