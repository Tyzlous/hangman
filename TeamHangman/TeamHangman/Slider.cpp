#include "Slider.h"



Slider::Slider(sf::Vector2f position, float width, std::string textKey, std::function<void(float value)> callback, bool isLocalized)
{
	window = HWindow::GetWindow();
	this->callback = callback;
	this->isLocalized = isLocalized;
	beingDragged = false;
	Init(position, width, textKey);
}


Slider::~Slider()
{
	if (line != nullptr)
	{
		delete line;
	}
	if (slider != nullptr)
	{
		delete slider;
	}
	if (lineTexture != nullptr)
	{
		delete lineTexture;
	}
	if (handleTexture != nullptr)
	{
		delete handleTexture;
	}
	if (label != nullptr)
	{
		delete label;
	}
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
			UpdatePosition();
			Callback();
			beingDragged = true;
		}
	}
	else
	{
		slider->setFillColor(sf::Color::Cyan);
	}
}
void Slider::Draw()
{
	window->draw(*line);
	window->draw(*slider);
	label->Draw();
}

void Slider::SetLineTexture(std::string texturePath)
{
	lineTexture = new sf::Texture();

	if (!lineTexture->loadFromFile(texturePath))
	{
		std::cout << "could not load texture from path " + texturePath + "\n";
	}
	else
	{
		line->setTexture(lineTexture, true);
	}
}

void Slider::SetHandleTexture(std::string texturePath)
{
	handleTexture = new sf::Texture();

	if (!handleTexture->loadFromFile(texturePath))
	{
		std::cout << "could not load texture from path " + texturePath + "\n";
	}
	else
	{
		slider->setTexture(handleTexture, true);
	}
}

void Slider::Init(sf::Vector2f position, float width, std::string textKey)
{
	line = new sf::RectangleShape(sf::Vector2f(width, 7.0f));
	sf::FloatRect rect = line->getLocalBounds();
	line->setOrigin(rect.left + rect.width * 0.5f, rect.top + rect.height * 0.5f);

	slider = new sf::RectangleShape(sf::Vector2f(line->getSize().y * 2.0f, line->getSize().y * 2.0f));
	rect = slider->getLocalBounds();
	slider->setOrigin(rect.left + rect.width * 0.5f, rect.top + rect.height * 0.5f);

	line->setFillColor(sf::Color::White);
	slider->setFillColor(sf::Color::White);

	line->setPosition(position);
	slider->setPosition(line->getGlobalBounds().left + line->getGlobalBounds().width, line->getGlobalBounds().top + line->getGlobalBounds().height * 0.5f);

	label = new LocalizedLabel(sf::Vector2f(line->getGlobalBounds().left, line->getPosition().y), textKey, 20, sf::Color::Magenta, isLocalized);
	label->OriginMiddle();
	label->SetPosition(sf::Vector2f(line->getGlobalBounds().left - label->GetGlobalBounds().width * 0.65f, label->GetPosition().y));
}

void Slider::UpdatePosition()
{
	if (line->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, slider->getPosition().y))
	{
		slider->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, slider->getPosition().y));
	}
	if (sf::Mouse::getPosition(*window).x < line->getGlobalBounds().left)
	{
		slider->setPosition(sf::Vector2f(line->getGlobalBounds().left, slider->getPosition().y));
	}
	if (sf::Mouse::getPosition(*window).x > line->getGlobalBounds().left + line->getGlobalBounds().width)
	{
		slider->setPosition(sf::Vector2f(line->getGlobalBounds().left + line->getGlobalBounds().width, slider->getPosition().y));
	}
}

void Slider::Callback()
{
	lineRectLeft = line->getGlobalBounds().left;
	sliderPosX = slider->getPosition().x - lineRectLeft;
	lineWidth = line->getGlobalBounds().width;
	value = sliderPosX / lineWidth;
	callback(value);
}
