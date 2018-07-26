#include "Label.h"



Label::Label()
{
	window = HWindow::GetWindow();
	baseColor = sf::Color::Red;

	font = new sf::Font();
	font->loadFromFile(FONT_NAME);

	text = new sf::Text("NAN", *font);
	text->setCharacterSize(30);
	text->setStyle(sf::Text::Bold);
	text->setFillColor(baseColor);
}

Label::Label(sf::Vector2f position, std::string text, int textSize, sf::Color textColor)
{
	window = HWindow::GetWindow();
	baseColor = textColor;

	font = new sf::Font();
	font->loadFromFile(FONT_NAME);

	this->text = new sf::Text(text, *font);
	this->text->setCharacterSize(30);
	this->text->setStyle(sf::Text::Bold);
	this->text->setFillColor(baseColor);
	this->text->setPosition(position);
}

Label::~Label()
{
	if (font != nullptr)
	{
		delete font;
	}
	if (text != nullptr)
	{
		delete text;
	}
}

void Label::Draw()
{
	if (window != nullptr)
	{
		if (isHighlighted)
		{
			text->setFillColor(highlightColor);
		}
		else
		{
			text->setFillColor(baseColor);
		}

		window->draw(*text);

		if (debugDrawEnabled)
		{
			DrawDebug();
		}
	}
}

void Label::DrawDebug()
{
	sf::Vector2f rectSize(text->getGlobalBounds().width, text->getGlobalBounds().height);
	sf::RectangleShape debugRectangle(rectSize);
	sf::Color transparentColor(0, 0, 0, 0);
	sf::Vector2f position = text->getPosition() + sf::Vector2f(0, text->getGlobalBounds().height / 4);

	debugRectangle.setPosition(position);
	debugRectangle.setFillColor(transparentColor);
	debugRectangle.setOutlineColor(sf::Color::Red);
	debugRectangle.setOutlineThickness(1);

	window->draw(debugRectangle);
}

sf::Vector2f Label::GetPosition()
{
	return text->getPosition();
}

void Label::SetPosition(sf::Vector2f position)
{
	text->setPosition(position);
}

void Label::Move(sf::Vector2f addPosition)
{
	text->setPosition(text->getPosition() + addPosition);
}

sf::FloatRect Label::GetGlobalBounds()
{
	return text->getGlobalBounds();
}

bool Label::Contains(sf::Vector2f point)
{
	return text->getGlobalBounds().contains(point);
}

void Label::EnableDebugDraw(bool enable) 
{
	debugDrawEnabled = enable;
}

void Label::SetColor(sf::Color color)
{
	baseColor = color;
}

void Label::Highlight(sf::Color color)
{
	highlightColor = color;
	isHighlighted = true;
}

void Label::DeHighlight()
{
	isHighlighted = false;
}
