#include "TextBox.h"



TextBox::TextBox()
{
}


TextBox::TextBox(sf::Vector2f position, unsigned int size, unsigned int maxLetterCount, std::string key)
{
	window = HWindow::GetWindow();
	this->maxLetterCount = maxLetterCount;
	TextInit(position, size);
	BoxInit(position, size);
}

TextBox::~TextBox()
{
	if (font != nullptr)
	{
		delete font;
	}
	if (text != nullptr)
	{
		delete text;
	}
	if (box != nullptr)
	{
		delete box;
	}
}

void TextBox::Update()
{
}

void TextBox::Draw()
{
	window->draw(*box);
	window->draw(*text);
}

void TextBox::SetString(std::string newString)
{
}

void TextBox::UpdateString(char charToAdd)
{
}

void TextBox::SetPosition(sf::Vector2f value)
{
}

sf::Vector2f TextBox::GetPosition()
{
	return sf::Vector2f();
}

bool TextBox::IsActive()
{
	return isActive;
}

void TextBox::TextInit(sf::Vector2f position, unsigned int size)
{
	font = new sf::Font();
	font->loadFromFile("arial.ttf");

	text = new sf::Text("HaHaHapa", *font);
	text->setCharacterSize(size);
	text->setFillColor(sf::Color::Red);
	text->setOrigin(text->getLocalBounds().left + text->getLocalBounds().width * 0.5f, text->getLocalBounds().top + text->getLocalBounds().height * 0.5f);
	text->setPosition(position);
}

void TextBox::BoxInit(sf::Vector2f position, unsigned int size)
{
	box = new sf::RectangleShape();
	box->setSize(sf::Vector2f(size * maxLetterCount, size * 1.1f));
	box->setOutlineColor(sf::Color::Red);
	box->setOutlineThickness(4);
	box->setOrigin(box->getLocalBounds().left + box->getLocalBounds().width * 0.5f, box->getLocalBounds().top + box->getLocalBounds().height * 0.5f);
	box->setPosition(position);

}

void TextBox::Centralize()
{
	text->setOrigin(text->getLocalBounds().left + text->getLocalBounds().width * 0.5f, text->getLocalBounds().top + text->getLocalBounds().height * 0.5f);
		
}
