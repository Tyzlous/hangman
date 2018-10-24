#include "Options.h"



Options::Options()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	InitializeSliders();
	InitializeTextBoxes();
	InitializeButtons();
	InitializeLanguagebuttons();
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
}


Options::~Options()
{
	for (int i = 0; i < callbackButtonAddresses.size(); i++)
	{
		delete callbackButtonAddresses[i];
	}
	if (slider != nullptr)
	{
		delete slider;
	}
	if (textBox != nullptr)
	{
		delete textBox;
	}
	if (sweFlagTexture != nullptr)
	{
		delete sweFlagTexture;
	}
	if (engFlagTexture != nullptr)
	{
		delete engFlagTexture;
	}
	if (flagRect1 != nullptr)
	{
		delete flagRect1;
	}
	if (flagRect2 != nullptr)
	{
		delete flagRect2;
	}
	if (languageLabel != nullptr)
	{
		delete languageLabel;
	}
	delete statDisplay;
	delete backgroundTexture;
	delete titleTexture;
	delete backgroundImage;
	delete titleImage;
}

void Options::Update()
{
	for (int i = 0; i < callbackButtonAddresses.size(); i++)
	{
	 callbackButtonAddresses[i]->update();
	}
	slider->Update();
	textBox->Update();
	UpdateLanguageButtons();
}

void Options::Draw()
{
	window->draw(*titleImage);
	window->draw(*backgroundImage);
	slider->Draw();
	textBox->Draw();
	window->draw(*flagRect1);
	window->draw(*flagRect2);
	languageLabel->Draw();
	statDisplay->Draw();
	for (int i = 0; i < callbackButtonAddresses.size(); i++)
	{
		callbackButtonAddresses[i]->draw();
	}
}

void Options::InitializeButtons()
{
	using namespace std::placeholders;
	sf::Vector2f topMod = sf::Vector2f(0.5f, 0.3f);
	sf::Vector2f topPosition = sf::Vector2f(window->getSize().x * topMod.x, window->getSize().y * topMod.y);

	menuButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "MENU", "KEY_MENU", sf::Vector2f(50.0f, 25.0f) , true);
	menuButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	menuButton->OriginMiddle();
	callbackButtonAddresses.push_back(&*menuButton); //  saving const addresses of every button made to delete them quickly later, add the address of any new button and they will be deleted.

	confirmNameButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "CONFIRM", "KEY_CONFIRM", sf::Vector2f(textBox->GetPosition().x, textBox->GetPosition().y + 35.0f), true);
	confirmNameButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	confirmNameButton->OriginMiddle();
	callbackButtonAddresses.push_back(&*confirmNameButton);

	saveButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "SAVE", "KEY_SAVE", sf::Vector2f(textBox->GetPosition().x, textBox->GetPosition().y + 70.0f), true);
	saveButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	saveButton->OriginMiddle();
	callbackButtonAddresses.push_back(&*saveButton);

	loadButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "LOAD", "KEY_LOAD", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.4f), true);
	loadButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	loadButton->OriginMiddle();
	callbackButtonAddresses.push_back(&*loadButton);

	createButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "CREATE", "KEY_CREATE", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.4f), true);
	createButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	createButton->OriginMiddle();
	callbackButtonAddresses.push_back(&*createButton);

	revertButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "REVERT", "KEY_REVERT", sf::Vector2f(textBox->GetPosition().x, textBox->GetPosition().y + 75.0f), true);
	revertButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	revertButton->OriginMiddle();
	callbackButtonAddresses.push_back(&*revertButton);

	if (textBox->GetLabelString().size() == 0)
	{
	confirmNameButton->disable();
	revertButton->disable();
	}
	loadButton->disable();
	createButton->disable();
	saveButton->disable();
	menuButton->disable();
}

void Options::InitializeLanguagebuttons()
{
	sf::Vector2f flagRectSize(255.0f, 160.0f);
	flagRect1 = new sf::RectangleShape(flagRectSize);
	flagRect2 = new sf::RectangleShape(flagRectSize);
	sweFlagTexture = new sf::Texture();
	engFlagTexture = new sf::Texture();

	sweFlagTexture->loadFromFile("resources/sweflag.jpg");
	engFlagTexture->loadFromFile("resources/engflag.jpg");

	flagRect1->setTexture(sweFlagTexture);
	flagRect2->setTexture(engFlagTexture);

	flagRect1->setPosition(window->getSize().x * 0.0f, window->getSize().y * 0.3f);
	flagRect2->setPosition(flagRect1->getPosition().x, flagRect1->getPosition().y + 220.f);

	languageLabel = new LocalizedLabel(sf::Vector2f(0.0f, 0.0f), "KEY_LANGUAGE", 30.0f, sf::Color::Red, true);
	languageLabel->OriginMiddle();
	languageLabel->SetPosition(sf::Vector2f(flagRect1->getPosition().x + flagRect1->getLocalBounds().width * 0.5f, flagRect1->getPosition().y - 45));
	
}

void Options::InitializeSliders()
{
	slider = new Slider(sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y * 0.3f), 170.0f, "KEY_VOLUME", std::bind(&Options::SetVolume, this, std::placeholders::_1), true);
	slider->SetLineTexture("resources/linetexture.jpg");
	slider->SetHandleTexture("resources/handletexture.png");
}

void Options::InitializeTextBoxes()
{
	textBox = new TextBox(sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y * 0.8f), 25, 15, "KEY_NAME");
	textBox->SetString(gamestate->playerData->GetUsername());

	statDisplay = new TextDisplay(sf::Vector2f(window->getSize().x * 0.7f, window->getSize().y * 0.3f), sf::Vector2f(350.0f, 350.0f), gamestate->playerData->GetUsername());
	UpdateStatDisplay();
}

void Options::UpdateLanguageButtons()
{
	if (flagRect1->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		flagRect1->setOutlineColor(sf::Color::Green);
		flagRect1->setOutlineThickness(3.0f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gamestate->currentLanguage != gamestate->Swedish)
		{
		gamestate->currentLanguage = gamestate->Swedish;
		callback();
		}

	}
	else flagRect1->setOutlineThickness(0.0f);
	
	if (flagRect2->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		flagRect2->setOutlineColor(sf::Color::Green);
		flagRect2->setOutlineThickness(3.0f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gamestate->currentLanguage != gamestate->English)
		{
			gamestate->currentLanguage = gamestate->English;
			callback();
		}
	}
	else flagRect2->setOutlineThickness(0.0f);

}
void Options::ButtonFunctions(std::string parameter)
{
	typedef Gamestate::State state;

	std::string menu = "MENU";
	std::string confirm = "CONFIRM";
	std::string save = "SAVE";
	std::string load = "LOAD";
	std::string create = "CREATE";
	std::string revert = "REVERT";

	if (menu.compare(parameter) == 0)
	{
		gamestate->currentState = state::MainMenu;
	}
	else if (confirm.compare(parameter) == 0)
	{
		confirmNameButton->disable();
		revertButton->disable();
		textBox->ConfirmCurrentString();
		if (gamestate->playerData->SearchDataFor(textBox->GetConfirmedString()))
		{
			loadButton->enable();
			createButton->disable();
		}
		else
		{
			createButton->enable();
			loadButton->disable();
		}
		saveButton->disable();
	}
	else if (revert.compare(parameter) == 0)
	{
		confirmNameButton->disable();
		textBox->SetString(textBox->GetConfirmedString());
		if (textBox->GetConfirmedString().size() != 0)
		{
			if (gamestate->playerData->SearchDataFor(textBox->GetConfirmedString()))
			{
				loadButton->enable();
				createButton->disable();
			}
			else
			{
				createButton->enable();
				loadButton->disable();
			}
		}
		saveButton->disable();
		revertButton->disable();
	}
	else if (save.compare(parameter) == 0)
	{
		gamestate->playerData->SaveData();
	}
	else if (load.compare(parameter) == 0)
	{
		gamestate->playerData->LoadData(textBox->GetConfirmedString());
		saveButton->enable();
		menuButton->enable();
		isDefaultProfile = false;
		UpdateStatDisplay();
	}
	else if (create.compare(parameter) == 0)
	{
		gamestate->playerData->ClearOldData();
		gamestate->playerData->SetUsername(textBox->GetConfirmedString());
		gamestate->playerData->SaveData();
		createButton->disable();
		loadButton->enable();
		saveButton->enable();
		menuButton->enable();
		isDefaultProfile = false;
		UpdateStatDisplay();
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
	languageLabel->UpdateChosenLanguage();
	for (int i = 0; i < callbackButtonAddresses.size(); i++)
	{
		callbackButtonAddresses[i]->UpdateChosenLanguage();
	}
	UpdateStatDisplay();
	textBox->UpdateLocalizedTitle();
}

void Options::SetSoundManager(HangmanSoundManager * soundmanager)
{
	soundManager = soundmanager;		
}

bool Options::TextBoxActive()
{
	return textBox->IsActive();
}

void Options::TextBoxProcess(sf::Uint32 value)
{
	if (value == 8) // 8 is backspace
	{
		textBox->PopBackString();
		createButton->disable();
		loadButton->disable();
		saveButton->disable();
		if (textBox->GetConfirmedString().compare(textBox->GetLabelString()) == 0)
		{
			revertButton->disable();
		}
		else revertButton->enable();
	}
	else if (value != 32) // 32 is spacebar
	{
		textBox->UpdateString((char) value);
		createButton->disable();
		loadButton->disable();
		saveButton->disable();
		if (textBox->GetConfirmedString().compare(textBox->GetLabelString()) == 0)
		{
			revertButton->disable();
		}
		else revertButton->enable();
	}

	if (textBox->IsNotEmpty())
	{
		confirmNameButton->enable();
	}
	else
	{
		confirmNameButton->disable();
	}
}

void Options::BindCallback(std::function<void()> cbFunction)
{
	callback = cbFunction;
}

void Options::UpdateStatDisplay()
{
	std::string text;
	float winPercentage = 0.0f;
	if (gamestate->playerData->GetGamesPlayed() > 0)
	{
		float a, b;
		a = gamestate->playerData->GetGamesWon();
		b = gamestate->playerData->GetGamesPlayed();
		winPercentage =  a / b;
		winPercentage *= 100;
	}
	statDisplay->SetTitle(gamestate->GetLocalizedString("KEY_PROFILE") + ": " + gamestate->playerData->GetUsername());
	text = gamestate->GetLocalizedString("KEY_TIME") + " " + gamestate->GetLocalizedString("KEY_PLAYED") + ": " + std::to_string((unsigned int)gamestate->playerData->GetTimePlayed().asSeconds()) + " " + gamestate->GetLocalizedString("KEY_SECONDS");
	statDisplay->SetText(text);
	text = gamestate->GetLocalizedString("KEY_MATCHES") + " " + gamestate->GetLocalizedString("KEY_PLAYED") + ": " + std::to_string(gamestate->playerData->GetGamesPlayed());
	statDisplay->NewLineOfText(text);
	text = gamestate->GetLocalizedString("KEY_WINS") + ": " + std::to_string(gamestate->playerData->GetGamesWon()) + " | " + std::to_string((unsigned int)winPercentage) + "%";
	statDisplay->NewLineOfText(text);
	text = gamestate->GetLocalizedString("KEY_GUESSES") + " " + gamestate->GetLocalizedString("KEY_MADE") + ": " + std::to_string(gamestate->playerData->GetTotalGuesses());
	statDisplay->NewLineOfText(text);
	text = gamestate->GetLocalizedString("KEY_CORRECT") + " " + gamestate->GetLocalizedString("KEY_GUESSES") + ": " + std::to_string(gamestate->playerData->GetTotalCorrectGuesses());
	statDisplay->NewLineOfText(text);
	if (isDefaultProfile)
	{
		text = text = gamestate->GetLocalizedString("KEY_HELLO") + ", " + gamestate->GetLocalizedString("KEY_LOAD") + " " + gamestate->GetLocalizedString("KEY_OR") + " " + gamestate->GetLocalizedString("KEY_CREATE") + " " + gamestate->GetLocalizedString("KEY_PROFILE") + " " + gamestate->GetLocalizedString("KEY_TO") + " " + gamestate->GetLocalizedString("KEY_CONTINUE");
		statDisplay->NewLineOfText(text);
	}
}

void Options::SetVolume(float modifier)
{
	soundManager->SetMasterVolume(modifier);
	std::cout << std::to_string(modifier) + "\n";
}
