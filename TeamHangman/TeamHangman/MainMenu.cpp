#include "MainMenu.h"



MainMenu::MainMenu()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	InitializeButtons();

	
}


MainMenu::~MainMenu()
{
	if (middleButton != nullptr)
	{
		delete middleButton;
	}
}

void MainMenu::update()
{
	topButton->update();
	middleButton->update();
	bottomButton->update();
}

void MainMenu::draw()
{
	topButton->draw();
	middleButton->draw();
	bottomButton->draw();
	// window->draw(me);
}

void MainMenu::fuckOff(std::string parameter)
{
	std::cout << "Prea fuck off, also " << parameter << std::endl;
}

void MainMenu::InitializeButtons()
{
	using namespace std::placeholders;
	sf::Vector2f topMod = sf::Vector2f(0.5f, 0.3f);
	sf::Vector2f topPosition = sf::Vector2f(window->getSize().x * topMod.x, window->getSize().y * topMod.y);

	
	topButton = new CallbackButton(std::bind(&MainMenu::fuckOff, this, _1), ", Erri is Great.", "Play", topPosition);
	topButton->OriginMiddle();
	
	middleButton = new CallbackButton(std::bind(&MainMenu::fuckOff, this, _1), ", I rike bread.", "Options", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.1f));
	middleButton->OriginMiddle();

	bottomButton = new CallbackButton(std::bind(&MainMenu::fuckOff, this, _1), ", I rike havrenoms.", "Quit", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.2f));
	bottomButton->OriginMiddle();
}

/*
#include <functional>
using namespace std::placeholders;
gameButton = new GameButton(std::bind(&Game::onButtonPress, this, _1));
void onButtonPress(std::string string)
{
std::cout << string << std::endl;
}
GameButton::GameButton(std::function<void(std::string)> callback)
{
	std::cout << "GameButton constructor called. " << std::endl;
	callback("Erri");
}
*/