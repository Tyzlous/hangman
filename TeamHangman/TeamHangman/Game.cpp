#include "Game.h"



Game::Game()
{
	InitializeState();
	InitializeTextures();
	KeyboardInit();
	WordVectorInit();
	LettersVectorInit();
	soundManager = nullptr;
	startupComplete = true;
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
	for (int i = 0; i < hangmanTextures.size(); i++)
	{
		delete hangmanTextures[i];
	}
	delete hangManRect;
	delete backgroundTexture;
	delete backgroundImage;
	delete titleTexture;
	delete titleImage;
}

void Game::InitializeState()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	UpdateChosenLanguage();
}

void Game::KeyboardInit()
{
	for (int i = 0; i < gameButtons.size(); i++)
	{
		delete gameButtons[i];
	}
	gameButtons.clear();
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
	words.clear();
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
	for (int i = 0; i < gameLetters.size(); i++)
	{
		delete gameLetters[i];
	}
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

void Game::EndGame()
{
	typedef Gamestate::State state;
	gamestate->currentState = state::EndGame;
}

void Game::InitializeTextures()
{
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
		titleImage->setSize(sf::Vector2f(350, 100));

		float centeredXPosition = (window->getSize().x / 2) - (titleImage->getSize().x / 2);
		titleImage->setPosition(centeredXPosition, 10);
	}
	sf::Texture* hangmanTexture;
	for (int i = 0; i < 8; i++)
	{
		hangmanTexture = new sf::Texture();
		hangmanTexture->loadFromFile(PICTURE_PATH + std::to_string(1 + i) + ".png");
		hangmanTextures.push_back(hangmanTexture);
	}
	hangManRect = new sf::RectangleShape(sf::Vector2f(window->getSize().x * 0.38f, window->getSize().y * 0.45f));
	hangManRect->setTexture(hangmanTextures[0]);
	hangManRect->setPosition(window->getSize().x - hangManRect->getLocalBounds().width, 0.0f);
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
	window->draw(*backgroundImage);
	window->draw(*titleImage);
	for (int i = 0; i < gameButtons.size(); i++)
	{
		gameButtons[i]->draw();
	}
	for (int i = 0; i < gameLetters.size(); i++)
	{
		gameLetters[i]->Draw();
	}
	window->draw(*hangManRect);
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
	if (startupComplete)
	{
		ResetGame();
	}
}

void Game::ResetGame()
{
	KeyboardInit();
	WordVectorInit();
	LettersVectorInit();
	for (int i = 0; i < gameButtons.size(); i++)
	{
		gameButtons[i]->enable();
	}
	correctLetters = 0;
	wrongGuesses = 0;
	hangManRect->setTexture(hangmanTextures[wrongGuesses]);
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
	bool guessIsCorrect = false;
	buttonPressed->disable();
	print(letter);
	for (int i = 0; i < gameLetters.size(); i++)
	{
		if (gameLetters[i]->CompareToMyLetter(letter))
		{
			guessIsCorrect = true;
			correctLetters++;
		}
	}
		if (guessIsCorrect)
		{
			if (correctLetters == gameLetters.size()) EndGame();
			else if (soundManager != nullptr) soundManager->PlayButtonPositive();
		}
		else
		{
			wrongGuesses++;
			if (wrongGuesses == 8) EndGame();
			if (soundManager != nullptr) soundManager->PlayButtonNegative();
			if (wrongGuesses < 8)
			{
				hangManRect->setTexture(hangmanTextures[wrongGuesses]);	
			}
		}
		gamestate->playerData->AddGuess(guessIsCorrect);
}

void Game::SetSoundManager(HangmanSoundManager * soundManager)
{
	this->soundManager = soundManager;
}

bool Game::GameWasWon()
{
	if (wrongGuesses == 8)
	{
		return false;
	}
	else
	{
		return true;
	}
}
