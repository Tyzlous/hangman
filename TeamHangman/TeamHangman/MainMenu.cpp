#include "MainMenu.h"



MainMenu::MainMenu()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	InitializeButtons();

	backgroundTexture = new sf::Texture();
	if (!backgroundTexture->loadFromFile(BACKGROUND_IMAGE_PATH))
	{
		std::cout << "cannot find MainMenu background image png\n";
	}
	else
	{
		backgroundTexture->setSmooth(true);
		backgroundImage = new sf::RectangleShape();
		backgroundImage->setTexture(backgroundTexture, true);
		backgroundImage->setSize(sf::Vector2f(window->getSize()));
	}

	titleTexture = new sf::Texture();
	if (!titleTexture->loadFromFile(TITLE_IMAGE_PATH))
	{
		std::cout << "cannot find MainMenu title image png\n";
	}
	else
	{
		titleTexture->setSmooth(true);
		titleImage = new sf::RectangleShape();
		titleImage->setTexture(titleTexture, true);
		titleImage->setSize(sf::Vector2f(350,100));

		float centeredXPosition = (window->getSize().x / 2) - (titleImage->getSize().x / 2);
		titleImage->setPosition(centeredXPosition, 10);
	}
}


MainMenu::~MainMenu()
{
	if (topButton != nullptr)
	{
		delete topButton;
	}
	if (middleButton != nullptr)
	{
		delete middleButton;
	}
	if (bottomButton != nullptr)
	{
		delete bottomButton;
	}
	if (backgroundTexture != nullptr)
	{
		delete backgroundTexture;
	}
	if (backgroundImage != nullptr)
	{
		delete backgroundImage;
	}
	if (titleTexture != nullptr)
	{
		delete titleTexture;
	}
	if (titleImage != nullptr)
	{
		delete titleImage;
	}
}

void MainMenu::update()
{
	topButton->update();
	middleButton->update();
	bottomButton->update();
}

void MainMenu::draw()
{
	if (backgroundImage != nullptr)
	{
		window->draw(*backgroundImage);
	}
	if (titleImage != nullptr)
	{
		window->draw(*titleImage);
	}
	topButton->draw();
	middleButton->draw();
	bottomButton->draw();
	// window->draw(me);
}

void MainMenu::fuckOff(std::string parameter)
{
	std::cout << "Prea fuck off, also " << parameter << std::endl;
}

void MainMenu::InitializeButtons()
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

void MainMenu::ChangeGamestate(std::string parameter)
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

/*
#include <functional>
using namespace std::placeholders;
gameButton = new GameButton(std::bind(&Game::onButtonPress, this, _1));
void onButtonPress(std::string string)
{
std::cout << string << std::endl;
}
GameButton::GameButton(std::function<void(std::string)> callback)
{
	std::cout << "GameButton constructor called. " << std::endl;
	callback("Erri");
}
*/