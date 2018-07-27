#include "Game.h"



Game::Game()
{
	Initialize();
	KeyboardInit();
}

Game::~Game()
{
	for (int i = 0; i < gameButtons.size(); i++)	
	{
		delete gameButtons[i];
	}
}

void Game::Initialize()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	UpdateChosenLanguage();
}

void Game::KeyboardInit()
{
	using namespace std::placeholders;
	std::string alphabet = GetLocalizedString("KEY_ALPHABET");
	std::string letter;

	float rowStartY = 0.5f;
	float rowStartX = 0.1f;
	float letterDist = 0.03f;
	int lettersPerRow = 12;

	for (int i = 0; i < alphabet.size(); i++)
	{
		letter = alphabet.at(i);
		if (i % lettersPerRow == 0)
		{
			if (i + 5 <= alphabet.size())
			{
				rowStartY += 0.1f;
				rowStartX = 0.1f;
			}

		}
		gameButtons.push_back(new CallbackButton(std::bind(&Game::OnLetterPressed, this, _1), letter, letter, sf::Vector2f(window->getSize().x * rowStartX, window->getSize().y * rowStartY), false));
		rowStartX += letterDist;
	}
}

void Game::Update()
{
	typedef Gamestate::State state;
	for (int i = 0; i < gameButtons.size(); i++)	
	{
		gameButtons[i]->update();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		gamestate->currentState = state::MainMenu;
	}
}

void Game::Draw()
{
	for (int i = 0; i < gameButtons.size(); i++)
	{
		gameButtons[i]->draw();
	}
}

void Game::UpdateChosenLanguage()
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

std::string Game::GetLocalizedString(std::string key)
{
	std::string localizedString = "NAN";

	if (pickedLanguage != nullptr)
	{
		dictionary::const_iterator value = pickedLanguage->find(key);

		//if we found a value
		if (value != pickedLanguage->end())
		{
			localizedString = value->second;
		}
	}
	return localizedString;
}

void Game::OnLetterPressed(std::string letter)
{
	std::cout << letter << std::endl;
}
