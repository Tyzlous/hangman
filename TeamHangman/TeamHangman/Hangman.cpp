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
	soundManager = new HangmanSoundManager();
	game = new Game();
	game->SetSoundManager(soundManager);
}

Hangman::~Hangman()
{
	delete mainMenu;
	delete game;
	delete soundManager;
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
			if (!soundManager->isMainMenuMusicPlaying)
			{
				soundManager->StartMainMenuMusic();
			}
			mainMenu->update();
			mainMenu->draw();
		}
		if (gamestate->currentState == state::Game)
		{
			if (!soundManager->isGameMusicPlaying)
			{
				soundManager->StartGameMusic();
			}
			game->Update();
			game->Draw();
			if (gamestate->currentState == state::MainMenu)
			{
				game->resetGame();
			}
		}
		if (gamestate->currentState == state::Quit)
		{
			window->close();
		}
		
		window->display();
	}
}
