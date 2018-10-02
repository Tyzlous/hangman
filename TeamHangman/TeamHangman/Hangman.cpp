#include "Hangman.h"



Hangman::Hangman()
{
	typedef Gamestate::State state;
	typedef Gamestate::Languages languages;
	gamestate = Gamestate::Get();
	gamestate->currentState = state::MainMenu;
	gamestate->currentLanguage = languages::Swedish;
	textInit();
	window = HWindow::GetWindow();
	mainMenu = new MainMenu();
	options = new Options();
	soundManager = new HangmanSoundManager();
	game = new Game();
	victory = new Victory();
	options->SetSoundManager(soundManager);
	game->SetSoundManager(soundManager);
	victory->SetSoundManager(soundManager);
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
	std::string test;
	std::string code = "ErriAlwaysWins";
	std::string string = text->getString();
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

					if (event.text.unicode == 8)
					{
						if (string.size() != 0)
						{
							string.pop_back();
							text->setString(string);

						}
					}
					else
					{
						string.push_back((char)event.text.unicode);
						text->setString(string);
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
		
		window->draw(*text);
		window->display();
	}
}

void Hangman::textInit()
{
	font = new sf::Font();
	font->loadFromFile("arial.ttf");

	text = new sf::Text("Derp", *font);
	text->setCharacterSize(35);
	text->setFillColor(sf::Color::Red);
}
