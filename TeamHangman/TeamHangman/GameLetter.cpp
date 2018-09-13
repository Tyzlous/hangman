#include "GameLetter.h"



GameLetter::GameLetter(sf::Vector2f position, std::string letter, int textSize, sf::Color textColor)
{
	window = HWindow::GetWindow();
	label = new Label(position, letter, textSize, textColor);
	bottomLine = new sf::RectangleShape(sf::Vector2f(30.0f, 3.0f));
	bottomLine->setPosition(sf::Vector2f(label->GetGlobalBounds().left + label->GetGlobalBounds().width * 0.5f, label->GetGlobalBounds().top + label->GetGlobalBounds().height));
	bottomLine->setFillColor(sf::Color::White);
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
	bool isFoundNow = false;
	if (myLetter.compare(letter) == 0 && !isFoundBefore)
	{
		isFoundNow = true;
	}
	if (isFoundNow == true)
	{
		isFoundBefore = true;
	}
	return isFoundNow;
}

void GameLetter::OriginMiddle()
{
	label->OriginMiddle();
	sf::FloatRect lineRect = bottomLine->getLocalBounds();
	bottomLine->setOrigin(lineRect.left + lineRect.width * 0.5f, lineRect.top + lineRect.height * 0.0f);
	bottomLine->setPosition(sf::Vector2f(label->GetGlobalBounds().left + label->GetGlobalBounds().width * 0.5f, label->GetGlobalBounds().top + label->GetGlobalBounds().height));
}

bool GameLetter::beenFound()
{
	return isFoundBefore;
}
