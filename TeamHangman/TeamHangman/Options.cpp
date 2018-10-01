#include "Options.h"



Options::Options()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	InitializeButtons();
	InitializeSliders();
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
	if (slider != nullptr)
	{
		delete slider;
	}

}

void Options::Update()
{
	menuButton->update();
	confirmNameButton->update();
	saveButton->update();
	slider->Update();
}

void Options::Draw()
{
	menuButton->draw();
	confirmNameButton->draw();
	saveButton->draw();
	slider->Draw();
}

void Options::InitializeButtons()
{
	using namespace std::placeholders;
	sf::Vector2f topMod = sf::Vector2f(0.5f, 0.3f);
	sf::Vector2f topPosition = sf::Vector2f(window->getSize().x * topMod.x, window->getSize().y * topMod.y);

	menuButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "MENU", "KEY_MENU", sf::Vector2f(50.0f, 25.0f) , true);
	menuButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	menuButton->OriginMiddle();

	confirmNameButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "CONFIRM", "KEY_CONFIRM", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.1f), true);
	confirmNameButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	confirmNameButton->OriginMiddle();

	saveButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "SAVE", "KEY_SAVE", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.2f), true);
	saveButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	saveButton->OriginMiddle();

}

void Options::InitializeSliders()
{
	slider = new Slider(sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y * 0.8f), 170.0f, "KEY_VOLUME", std::bind(&Options::SetVolume, this, std::placeholders::_1), true);
	slider->SetLineTexture("resources/linetexture.jpg");
	slider->SetHandleTexture("resources/handletexture.png");
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

void Options::SetSoundManager(HangmanSoundManager * soundmanager)
{
	soundManager = soundmanager;		
}

void Options::SetVolume(float modifier)
{
	soundManager->SetMasterVolume(modifier);
	std::cout << std::to_string(modifier) + "\n";
}
