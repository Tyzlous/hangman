#include "Hangman.h"



Hangman::Hangman()
{
	typedef Gamestate::State state;
	typedef Gamestate::Languages languages;
	gamestate = Gamestate::Get();
	gamestate->currentState = state::MainMenu;
	gamestate->currentLanguage = languages::Swedish;

	window = HWindow::GetWindow();
	mainMenu = new MainMenu();
}

Hangman::~Hangman()
{
}

void Hangman::Start()
{
	typedef Gamestate::State state;

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
