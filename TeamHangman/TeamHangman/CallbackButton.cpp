#include "CallbackButton.h"



CallbackButton::CallbackButton(std::function<void(std::string, CallbackButton*)> callback, std::string callbackString, std::string buttonText, sf::Vector2f position, bool isLocalized)
{
	window = HWindow::GetWindow();
	callbackParameter = callbackString;
	this->callback = callback;

	label = new LocalizedLabel(position, buttonText, 30, sf::Color::White, isLocalized);
	label->EnableDebugDraw(false);
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
	if (texture != nullptr)
	{
		delete texture;
	}
	if (backgroundImage != nullptr)
	{
		delete backgroundImage;
	}
}

void CallbackButton::update()
{
	if (label->Contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		label->Highlight();
		if (backgroundImage != nullptr)
		{
			backgroundImage->setFillColor(sf::Color::Magenta);
		}

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
		if (backgroundImage != nullptr)
		{
			backgroundImage->setFillColor(sf::Color::White);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !label->Contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
		{
			pressedOutside = true;
		}
	}
}

void CallbackButton::draw()
{
	if (enabled)
	{
		if (backgroundImage != nullptr)
		{
			window->draw(*backgroundImage);
		}
		label->Draw();
	}
}

void CallbackButton::activate()
{
	if (enabled)
	{
		callback(callbackParameter, this);
	}
}
void CallbackButton::disable()
{
	enabled = false;
}
void CallbackButton::enable()
{
	enabled = true;
}
void CallbackButton::UpdateChosenLanguage()
{
	label->UpdateChosenLanguage();
	if (texture != nullptr)
	{
	backgroundImage->setSize(sf::Vector2f(label->GetGlobalBounds().width * 1.1f, label->GetGlobalBounds().height * 1.2f));
	backgroundImage->setOrigin(label->GetOrigin());
	backgroundImage->setPosition(label->GetPosition());
	OriginMiddle();
	}
}
void CallbackButton::OriginMiddle()
{
	label->OriginMiddle();

	if (backgroundImage != nullptr)
	{
		sf::FloatRect backgroundImageRect = backgroundImage->getLocalBounds();
		backgroundImage->setOrigin(backgroundImageRect.left + backgroundImageRect.width * 0.5f, backgroundImageRect.top + backgroundImageRect.height * 0.5f);
	}
}

void CallbackButton::SetOrigin(sf::Vector2f modifier)
{
	label->SetOrigin(modifier);
	if (backgroundImage != nullptr)
	{
		backgroundImage->setOrigin(label->GetOrigin());
	}
}

void CallbackButton::SetTexture(std::string texturePath)
{
	texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath))
	{
		std::cout << "cannot find menuButton png\n";
	}
	else
	{
		texture->setSmooth(true);
		backgroundImage = new sf::RectangleShape();
		backgroundImage->setTexture(texture, true);
		backgroundImage->setOrigin(label->GetOrigin());
		backgroundImage->setSize(sf::Vector2f(label->GetGlobalBounds().width * 1.1f, label->GetGlobalBounds().height * 1.2f));
		backgroundImage->setPosition(label->GetPosition());
	}
}

sf::Vector2f CallbackButton::GetOrigin()
{
	return label->GetOrigin();
}
