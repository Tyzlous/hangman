#include "Options.h"



Options::Options()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	InitializeButtons();
}


Options::~Options()
{
	if (menuButton != nullptr)
	{
		delete menuButton;
	}
	if (confirmNameButton != nullptr)
	{ 
		delete confirmNameButton;
	}
	if (saveButton != nullptr)
	{
		delete saveButton;
	}

}

void Options::Update()
{
	menuButton->update();
	confirmNameButton->update();
	saveButton->update();
}

void Options::Draw()
{
	menuButton->draw();
	confirmNameButton->draw();
	saveButton->draw();
}

void Options::InitializeButtons()
{
	using namespace std::placeholders;
	sf::Vector2f topMod = sf::Vector2f(0.5f, 0.3f);
	sf::Vector2f topPosition = sf::Vector2f(window->getSize().x * topMod.x, window->getSize().y * topMod.y);

	menuButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "MENU", "KEY_MENU", topPosition, true);
	menuButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	menuButton->OriginMiddle();

	confirmNameButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "CONFIRM", "KEY_CONFIRM", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.1f), true);
	confirmNameButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	confirmNameButton->OriginMiddle();

	saveButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "SAVE", "KEY_SAVE", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.2f), true);
	saveButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	saveButton->OriginMiddle();

}

void Options::ButtonFunctions(std::string parameter)
{
	typedef Gamestate::State state;

	std::string menu = "MENU";
	std::string confirm = "CONFIRM";
	std::string save = "SAVE";

	if (menu.compare(parameter) == 0)
	{
		gamestate->currentState = state::MainMenu;
	}
	else if (confirm.compare(parameter) == 0)
	{
		gamestate->currentState = state::Options;
	}
	else if (save.compare(parameter) == 0)
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
