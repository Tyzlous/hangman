#include "Hangman.h"



Hangman::Hangman()
{
	typedef Gamestate::State state;
	typedef Gamestate::Languages languages;
	gamestate = Gamestate::Get();
	gamestate->currentState = state::Options;
	gamestate->currentLanguage = languages::Swedish;
	window = HWindow::GetWindow();
	mainMenu = new MainMenu();
	options = new Options();
	soundManager = new HangmanSoundManager();
	game = new Game();
	victory = new Victory();
	options->SetSoundManager(soundManager);
	game->SetSoundManager(soundManager);
	victory->SetSoundManager(soundManager);
	options->BindCallback(std::bind(&Hangman::UpdateLanguage, this));
}

Hangman::~Hangman()
{
	delete mainMenu;
	delete game;
	delete soundManager;
	delete victory;
	delete options;

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
			if (event.type == sf::Event::TextEntered)
			{
				if (options->TextBoxActive())
				{
					if (event.text.unicode < 128)
					{
						std::cout << "ASCII character number typed: " << event.text.unicode << std::endl;
						options->TextBoxProcess(event.text.unicode);
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
			if (!soundManager->isMainMenuMusicPlaying)
			{
				soundManager->StartMainMenuMusic();
			}
			options->Update();
			options->Draw();
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

void Hangman::UpdateLanguage()
{
	victory->UpdateLanguage();
	game->UpdateChosenLanguage();
	mainMenu->UpdateLanguage();
	options->UpdateChosenLanguage();
}
