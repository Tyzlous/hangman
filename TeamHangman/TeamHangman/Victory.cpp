#include "Victory.h"



Victory::Victory()
{
	InitializeState();
	InitializeButtons();
	playMusic = true;
}


Victory::~Victory()
{
	delete winText;
	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}	
}

void Victory::Update()
{
	if (playMusic)
	{
		if (soundManager != nullptr) soundManager->PlayVictory();
		playMusic = false;
	}
	for (int i = 0; i < buttons.size(); i++)	
	{
		buttons[i]->update();
	}
}

void Victory::Draw()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw();
	}
	winText->Draw();
}

void Victory::SetSoundManager(HangmanSoundManager * soundManager)
{
	this->soundManager = soundManager;
}

void Victory::UpdateLanguage()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->UpdateChosenLanguage();
	}
	winText->UpdateChosenLanguage();
}

void Victory::InitializeState()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	winText = new LocalizedLabel(sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y * 0.15f), "KEY_YOU_WIN", 60, sf::Color::Green, true);
	winText->OriginMiddle();
}

void Victory::InitializeButtons()
{
	using namespace std::placeholders;
	sf::Vector2f topMod = sf::Vector2f(0.5f, 0.3f);
	sf::Vector2f topPosition = sf::Vector2f(window->getSize().x * topMod.x, window->getSize().y * topMod.y);
	buttons.push_back(new CallbackButton(std::bind(&Victory::ChangeGamestate, this, _1), "MAIN MENU", "KEY_MENU", topPosition, true));;
	buttons.push_back(new CallbackButton(std::bind(&Victory::ChangeGamestate, this, _1), "QUIT", "KEY_QUIT", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.2f), true));
	for (int i = 0; i < buttons.size(); i++)	
	{
		buttons[i]->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
		buttons[i]->OriginMiddle();
	}
}

void Victory::ChangeGamestate(std::string parameter)
{
	typedef Gamestate::State state;

	std::string menu = "MAIN MENU";
	std::string quit = "QUIT";

	if (menu.compare(parameter) == 0)
	{
		gamestate->currentState = state::MainMenu;
		playMusic = true;
	}
	else if (quit.compare(parameter) == 0)
	{
		gamestate->currentState = state::Quit;
	}
}