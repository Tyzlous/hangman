#include "Game.h"



Game::Game()
{
	InitializeState();
	KeyboardInit();
	WordVectorInit();
}

Game::~Game()
{
	for (int i = 0; i < gameButtons.size(); i++)	
	{
		delete gameButtons[i];
	}
}

void Game::InitializeState()
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

void Game::WordVectorInit()
{
	std::string baseFilePath = "resources/words";
	std::string language = GetLocalizedString("KEY_ABBREVIATION");
	std::string fileType = ".txt";
	std::string fullPath = baseFilePath + language + fileType;
	
	std::fstream file;
	std::string line;
	file.open(fullPath, std::ios::in);
	if (!file.is_open())
	{
		std::cout << "error opening file\n";
	}
	else
	{
		while (std::getline(file, line))
		{
			words.push_back(line);
		}
		file.close();
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

std::string Game::GetRandomLine()
{
	unsigned int max = words.size() - 1;
	unsigned int min = 0;
	unsigned int randomValue = rand() % (max - min + 1) + min;
	
	std::string randomLine = words[randomValue];
	
	return randomLine;
}

void Game::print(std::string string)
{
	std::cout << string << std::endl;
}

void Game::OnLetterPressed(std::string letter)
{
	std::cout << letter << std::endl;
	std::cout << GetRandomLine() << std::endl;
}
