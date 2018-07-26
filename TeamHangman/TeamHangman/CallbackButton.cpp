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
}

void CallbackButton::update()
{
	if (label->Contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		label->Highlight();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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
		label->DeHighlight();
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
	label->UpdateChosenLanguage();
}
