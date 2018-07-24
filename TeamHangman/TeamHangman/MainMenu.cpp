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
