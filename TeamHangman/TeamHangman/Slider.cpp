#include "Slider.h"



Slider::Slider(sf::Vector2f position, float width, std::string textKey, std::function<void(float value)> callback, bool isLocalized)
{
	window = HWindow::GetWindow();
	Init(position, width, textKey);
	this->callback = callback;
	this->isLocalized = isLocalized;
	beingDragged = false;

}


Slider::~Slider()
{
	delete line;
	delete slider;
}

void Slider::Update()
{
	if (beingDragged & !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		beingDragged = false;
	}
	if (slider->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)) || beingDragged)
	{
		slider->setFillColor(sf::Color::White);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (line->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, slider->getPosition().y))
			{
				slider->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, slider->getPosition().y));
			}

			beingDragged = true;
		}
	}
	else
	{
		slider->setFillColor(sf::Color::Green);
	}
}
void Slider::Draw()
{
	window->draw(*line);
	window->draw(*slider);
}

void Slider::Init(sf::Vector2f position, float width, std::string textKey)
{
	line = new sf::RectangleShape(sf::Vector2f(width, 7.0f));
	sf::FloatRect rect = line->getLocalBounds();
	line->setOrigin(rect.left + rect.width * 0.5f, rect.top + rect.height * 0.5f);

	slider = new sf::RectangleShape(sf::Vector2f(line->getSize().y * 2.0f, line->getSize().y * 2.0f));
	rect = slider->getLocalBounds();
	slider->setOrigin(rect.left + rect.width * 0.5f, rect.top + rect.height * 0.5f);

	line->setFillColor(sf::Color::Green);
	slider->setFillColor(sf::Color::Green);

	line->setPosition(position);
	slider->setPosition(line->getGlobalBounds().left + line->getGlobalBounds().width, line->getGlobalBounds().top + line->getGlobalBounds().height * 0.5f);
}
