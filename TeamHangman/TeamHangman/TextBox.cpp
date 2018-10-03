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
	if (box->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			isActive = true;
		}
		if (isActive)
		{
			box->setOutlineColor(sf::Color::Blue);
		}
		else
		{
			box->setOutlineColor(sf::Color::Green);
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			isActive = false;
		}
		if (isActive)
		{
			box->setOutlineColor(sf::Color::Blue);
		}
		else
		{
			box->setOutlineColor(sf::Color::Red);
		}
	}
}

void TextBox::Draw()
{
	window->draw(*box);
	window->draw(*text);
}

void TextBox::SetString(std::string newString)
{
	text->setString(newString);
	Centralize();
}

void TextBox::UpdateString(char charToAdd)
{
	std::string string = text->getString();
	if (string.size() < maxLetterCount)
	{
	string.push_back(charToAdd);
	text->setString(string);
	Centralize();
	}
}

void TextBox::PopBackString()
{
	std::string string = text->getString();
	if (string.size() > 0)
	{
		string.pop_back();
		text->setString(string);
		Centralize();
	}
}

void TextBox::SetPosition(sf::Vector2f value)
{
	text->setPosition(value);
	box->setPosition(value);
}

sf::Vector2f TextBox::GetPosition()
{
	return text->getPosition();
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
	text->setPosition(box->getPosition());
}
