#include "GameLetter.h"



GameLetter::GameLetter(sf::Vector2f position, std::string letter, int textSize, sf::Color textColor)
{
	window = HWindow::GetWindow();
	bottomLine = new sf::RectangleShape(sf::Vector2f(30.0f, 3.0f));
	bottomLine->setPosition(position);
	bottomLine->setFillColor(sf::Color::White);
	label = new Label(sf::Vector2f(bottomLine->getGlobalBounds().left + bottomLine->getGlobalBounds().width * 0.5f, bottomLine->getGlobalBounds().top + bottomLine->getGlobalBounds().height), letter, textSize, textColor);
	myLetter = letter;
}

GameLetter::GameLetter()
{
	window = HWindow::GetWindow();
	label = new Label();
	bottomLine = new sf::RectangleShape(sf::Vector2f(50.0f, 10.0f));
	myLetter = "null";
}

GameLetter::~GameLetter()
{
	if (label != nullptr)
	{
		delete label;
	}
	if (bottomLine != nullptr)
	{
		delete bottomLine;
	}
}

void GameLetter::Update()
{
}

void GameLetter::Draw()
{
	if (isFoundBefore)
	{
		label->Draw();
	}
	window->draw(*bottomLine);
}

bool GameLetter::CompareToMyLetter(std::string letter)
{
	if (myLetter.compare(letter) == 0)
	{
		isFoundBefore = true;
	}

	return myLetter.compare(letter) == 0;
}

void GameLetter::OriginMiddle()
{
	label->OriginMiddle();
	sf::FloatRect lineRect = bottomLine->getLocalBounds();
	bottomLine->setOrigin(lineRect.left + lineRect.width * 0.5f, lineRect.top + lineRect.height * 0.0f);
	label->SetPosition(sf::Vector2f(bottomLine->getGlobalBounds().left + bottomLine->getGlobalBounds().width * 0.5f, bottomLine->getGlobalBounds().top - 15.0f));
}
