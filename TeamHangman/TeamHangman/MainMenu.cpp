#include "MainMenu.h"



MainMenu::MainMenu()
{
	using namespace std::placeholders;
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	middleButton = new CallbackButton(std::bind(&MainMenu::fuckOff, this, _1), ", I rike bread.", "KEY_YOU_WIN", sf::Vector2f(300,300));
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
	middleButton->update();
}

void MainMenu::draw()
{
	middleButton->draw();
	// window->draw(me);
}

void MainMenu::fuckOff(std::string parameter)
{
	std::cout << "Prea fuck off, also " << parameter << std::endl;
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