#include "Options.h"



Options::Options()
{
	window = HWindow::GetWindow();
}


Options::~Options()
{
}

void Options::Update()
{
}

void Options::Draw()
{
}

void Options::InitializeButtons()
{
	using namespace std::placeholders;
	sf::Vector2f topMod = sf::Vector2f(0.5f, 0.3f);
	sf::Vector2f topPosition = sf::Vector2f(window->getSize().x * topMod.x, window->getSize().y * topMod.y);

	topButton = new CallbackButton(std::bind(&MainMenu::ChangeGamestate, this, _1), "PLAY", "KEY_PLAY", topPosition, true);
	topButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	topButton->OriginMiddle();

	middleButton = new CallbackButton(std::bind(&MainMenu::ChangeGamestate, this, _1), "OPTIONS", "KEY_OPTIONS", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.1f), true);
	middleButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	middleButton->OriginMiddle();

	bottomButton = new CallbackButton(std::bind(&MainMenu::ChangeGamestate, this, _1), "QUIT", "KEY_QUIT", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.2f), true);
	bottomButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	bottomButton->OriginMiddle();
}

void Options::ChangeGamestate(std::string parameter)
{
	typedef Gamestate::State state;

	std::string play = "PLAY";
	std::string options = "OPTIONS";
	std::string quit = "QUIT";

	if (play.compare(parameter) == 0)
	{
		gamestate->currentState = state::Game;
	}
	else if (options.compare(parameter) == 0)
	{
		gamestate->currentState = state::Options;
	}
	else if (quit.compare(parameter) == 0)
	{
		gamestate->currentState = state::Quit;
	}
}
void Options::UpdateChosenLanguage()
{
	typedef Gamestate::Languages languages;
	if (gamestate != nullptr)
	{
		switch (gamestate->currentLanguage)
		{
		case languages::English:
			pickedLanguage = &Localization::english;
			break;
		case languages::Swedish:
			pickedLanguage = &Localization::swedish;
			break;
		default:
			pickedLanguage = &Localization::english;
			std::cout << "Could not find desired language, defaulting to english.\n";
			break;
		}
	}
}
