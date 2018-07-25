#include "CallbackButton.h"



CallbackButton::CallbackButton(std::function<void(std::string)> callback, std::string string)
{
	window = HWindow::GetWindow();
	callbackParameter = string;
	this->callback = callback;
	/*label = new Label()*/
}

CallbackButton::CallbackButton()
{
}


CallbackButton::~CallbackButton()
{
}

void CallbackButton::update()
{

	if (label->Contains((sf::Vector2f)sf::Mouse::getPosition()))
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
	/*label->draw();*/
}

void CallbackButton::activate()
{
	callback(callbackParameter);
}
