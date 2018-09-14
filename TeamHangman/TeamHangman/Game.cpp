#include "Game.h"



Game::Game()
{
	InitializeState();
	KeyboardInit();
	WordVectorInit();
	LettersVectorInit();
	soundManager = nullptr;
}

Game::~Game()
{
	for (int i = 0; i < gameButtons.size(); i++)	
	{
		delete gameButtons[i];
	}
	for (int i = 0; i < gameLetters.size(); i++)
	{	
		delete gameLetters[i];
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
		gameButtons.push_back(new CallbackButton(std::bind(&Game::OnLetterPressed, this, _1, _2), letter, letter, sf::Vector2f(window->getSize().x * rowStartX, window->getSize().y * rowStartY), false));
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

void Game::LettersVectorInit()
{
	gameLetters.clear();
	std::string word = GetRandomLine();
	std::cout << word << std::endl;
	std::string letter;
	float letterSpacing;
	float firstLetterPos;
	float lastLetterPos;
	if (word.size() <= 10)
	{
		firstLetterPos = 0.3f;
		lastLetterPos = 0.7f - firstLetterPos;
	}
	else if (word.size() <= 30)
	{
		firstLetterPos = 0.1f;
		lastLetterPos = 0.9f - firstLetterPos;
	}
	else
	{
		firstLetterPos = 0.05f;
		lastLetterPos = 0.95f - firstLetterPos;
	}
	letterSpacing = window->getSize().x * lastLetterPos / word.size();
	if (gameLetters.empty()) 
	{
		for (int i = 0; i < word.size(); i++)
		{
			letter = word.at(i);
			gameLetters.push_back(new GameLetter(sf::Vector2f(window->getSize().x * firstLetterPos + (letterSpacing * i), window->getSize().y * 0.5f), letter, 40, sf::Color::Magenta));
		}
	}
	for (int i = 0; i < gameLetters.size(); i++)
	{
		gameLetters[i]->OriginMiddle();
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
	for (int i = 0; i < gameLetters.size(); i++)
	{
		gameLetters[i]->Draw();
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

void Game::ResetGame()
{
	LettersVectorInit();
	for (int i = 0; i < gameButtons.size(); i++)
	{
		gameButtons[i]->enable();
	}
	correctLetters = 0;
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
	unsigned int max = words.size();
	unsigned int randomValue = rand() % max;
	
	std::string randomLine = words.at(randomValue);
	
	return randomLine;
}

void Game::print(std::string string)
{
	std::cout << string << std::endl;
}

void Game::OnLetterPressed(std::string letter, CallbackButton* buttonPressed)
{
	bool correctGuess = false;
	buttonPressed->disable();
	print(letter);
	for (int i = 0; i < gameLetters.size(); i++)
	{
		if (gameLetters[i]->CompareToMyLetter(letter))
		{
			correctGuess = true;
			correctLetters++;
		}
	}
		if (correctGuess)
		{
			if (soundManager != nullptr && correctLetters == gameLetters.size()) soundManager->PlayVictory();
			else if (soundManager != nullptr) soundManager->PlayButtonPositive();
		}
		else
		{
			if (soundManager != nullptr) soundManager->PlayButtonNegative();

		}
}

void Game::SetSoundManager(HangmanSoundManager * soundManager)
{
	this->soundManager = soundManager;
}
