#include "CallbackButton.h"



CallbackButton::CallbackButton(std::function<void(std::string)> callback, std::string callbackString, std::string buttonText, sf::Vector2f position)
{
	window = HWindow::GetWindow();
	callbackParameter = callbackString;
	this->callback = callback;
	label = new LocalizedLabel(position, buttonText, 30, sf::Color::White);
	label->EnableDebugDraw(true);
}

CallbackButton::CallbackButton()
{
}

CallbackButton::~CallbackButton()
{
	if (label != nullptr)
	{
		delete label;
	}
}

void CallbackButton::update()
{

	if (label->Contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		label->Highlight();
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressedOutside)
		{
			pressedOutside = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressedOutside)
		{
				isPressed = true;
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPressed == true)
		{
				activate();
				isPressed = false;
		}
	}
	else
	{
		isPressed = false;
		label->DeHighlight();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !label->Contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
		{
			pressedOutside = true;
		}
	}
}

void CallbackButton::draw()
{
	label->Draw();
}

void CallbackButton::activate()
{
	callback(callbackParameter);
}
void CallbackButton::UpdateChosenLanguage()
{
	//label->UpdateChosenLanguage();
}
void CallbackButton::OriginMiddle()
{
	label->OriginMiddle();
}

void CallbackButton::SetOrigin(sf::Vector2f modifier)
{
	label->SetOrigin(modifier);
}
