#include "Hangman.h"



Hangman::Hangman()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	mainMenu = new MainMenu();
}


Hangman::~Hangman()
{
}

void Hangman::Start()
{
	typedef Gamestate::State state;
	gamestate->currentState = state::MainMenu;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		/*draw after clear*/

		if (gamestate->currentState == state::MainMenu)
		{
			mainMenu->update();
			mainMenu->draw();
		}
		if (gamestate->currentState == state::Game)
		{

		}
		if (gamestate->currentState == state::Quit)
		{
			window->close();
		}
		
		window->display();
	}
}
