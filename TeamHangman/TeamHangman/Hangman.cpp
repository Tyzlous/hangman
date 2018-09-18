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
	victory = new Victory();
}

Hangman::~Hangman()
{
	delete mainMenu;
	delete game;
	delete soundManager;
	delete victory;
}

void Hangman::Start()
{
	typedef Gamestate::State state;
	std::string test;
	std::string code = "ErriAlwaysWins";
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					std::cout << "ASCII character number typed: " << event.text.unicode << std::endl;

					if (event.text.unicode == 8 && test.size() != 0)
					{
						test.pop_back();
						std::cout << test << std::endl;
					}
					else
					{
						test.push_back((char)event.text.unicode);
						std::cout << test << std::endl;
					}

					if (code.compare(test) == 0)
					{
						gamestate->currentState = state::Victory;
						std::cout << "Thing\n";
					}
				}
			}

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
		if (gamestate->currentState == state::Options)
		{
			
		}
		if (gamestate->currentState == state::Game)
		{
			if (!soundManager->isGameMusicPlaying)
			{
				soundManager->StartGameMusic();
			}
			game->Update();
			game->Draw();
			if (gamestate->currentState != state::Game)
			{
				game->ResetGame();
			}
		}
		if (gamestate->currentState == state::Victory)
		{
			victory->Update();
			victory->Draw();
		}
		if (gamestate->currentState == state::Quit)
		{
			window->close();
		}
		
		window->display();
	}
}

void Hangman::GameDataEvent()
{
}
