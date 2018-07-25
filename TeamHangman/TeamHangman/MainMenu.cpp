#include "MainMenu.h"



MainMenu::MainMenu()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();

}


MainMenu::~MainMenu()
{
}

void MainMenu::update()
{
	// check mousepos for buttons etc
}

void MainMenu::draw()
{
	// window->draw(me);
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