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
}

void MainMenu::draw()
{
	topButton->draw();
	middleButton->draw();
	// window->draw(me);
}

void MainMenu::fuckOff(std::string parameter)
{
	std::cout << "Prea fuck off, also " << parameter << std::endl;
}

void MainMenu::InitializeButtons()
{
	using namespace std::placeholders;
	sf::Vector2f top = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y * 0.4f);
	sf::Vector2f middle = (sf::Vector2f)window->getSize() * 0.5f;
	
	topButton = new CallbackButton(std::bind(&MainMenu::fuckOff, this, _1), ", Erri is Great.", "Hello, first button here", top);
	topButton->OriginMiddle();
	
	middleButton = new CallbackButton(std::bind(&MainMenu::fuckOff, this, _1), ", I rike bread.", "I are button, prea press", middle);
	middleButton->OriginMiddle();
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