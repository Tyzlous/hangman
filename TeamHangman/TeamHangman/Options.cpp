#include "Options.h"



Options::Options()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	InitializeSliders();
	InitializeTextBoxes();
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
	if (loadButton != nullptr)
	{
		delete loadButton;
	}
	if (createButton != nullptr)
	{
		delete createButton;
	}
	if (slider != nullptr)
	{
		delete slider;
	}
	if (textBox != nullptr)
	{
		delete textBox;
	}
}

void Options::Update()
{
	menuButton->update();
	confirmNameButton->update();
	saveButton->update();
	loadButton->update();
	createButton->update();
	slider->Update();
	textBox->Update();
}

void Options::Draw()
{
	menuButton->draw();
	confirmNameButton->draw();
	saveButton->draw();
	loadButton->draw();
	createButton->draw();
	slider->Draw();
	textBox->Draw();
}

void Options::InitializeButtons()
{
	using namespace std::placeholders;
	sf::Vector2f topMod = sf::Vector2f(0.5f, 0.3f);
	sf::Vector2f topPosition = sf::Vector2f(window->getSize().x * topMod.x, window->getSize().y * topMod.y);

	menuButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "MENU", "KEY_MENU", sf::Vector2f(50.0f, 25.0f) , true);
	menuButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	menuButton->OriginMiddle();

	confirmNameButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "CONFIRM", "KEY_CONFIRM", sf::Vector2f(textBox->GetPosition().x, textBox->GetPosition().y + 35.0f), true);
	confirmNameButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	confirmNameButton->OriginMiddle();

	saveButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "SAVE", "KEY_SAVE", sf::Vector2f(textBox->GetPosition().x, textBox->GetPosition().y + 70.0f), true);
	saveButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	saveButton->OriginMiddle();

	loadButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "LOAD", "KEY_LOAD", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.4f), true);
	loadButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	loadButton->OriginMiddle();

	createButton = new CallbackButton(std::bind(&Options::ButtonFunctions, this, _1), "CREATE", "KEY_CREATE", sf::Vector2f(topPosition.x, topPosition.y + window->getSize().y * 0.4f), true);
	createButton->SetTexture("resources/menuButton.png"); // very important to setTexture before OriginMiddle, because reasons
	createButton->OriginMiddle();
	
	if (textBox->GetLabelString().size() == 0)
	{
	confirmNameButton->disable();
	}
	loadButton->disable();
	createButton->disable();
	saveButton->disable();
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
}

void Options::ButtonFunctions(std::string parameter)
{
	typedef Gamestate::State state;

	std::string menu = "MENU";
	std::string confirm = "CONFIRM";
	std::string save = "SAVE";
	std::string load = "LOAD";
	std::string create = "CREATE";

	if (menu.compare(parameter) == 0)
	{
		gamestate->currentState = state::MainMenu;
	}
	else if (confirm.compare(parameter) == 0)
	{
		textBox->ConfirmCurrentString();
		if (gamestate->playerData->SearchDataFor(textBox->GetString()))
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
	else if (save.compare(parameter) == 0)
	{
		gamestate->playerData->SaveData();
	}
	else if (load.compare(parameter) == 0)
	{
		gamestate->playerData->LoadData(textBox->GetString());
		saveButton->enable();
	}
	else if (create.compare(parameter) == 0)
	{
		gamestate->playerData->SetUsername(textBox->GetString());
		gamestate->playerData->SaveData();
		createButton->disable();
		loadButton->enable();
		saveButton->enable();
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

bool Options::TextBoxActive()
{
	return textBox->IsActive();
}

void Options::TextBoxProcess(sf::Uint32 value)
{
	if (value == 8)
	{
		textBox->PopBackString();
		createButton->disable();
		loadButton->disable();
		saveButton->disable();
	}
	else if (value != 32) // 32 is spacebar
	{
		textBox->UpdateString((char) value);
		createButton->disable();
		loadButton->disable();
		saveButton->disable();
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

void Options::SetVolume(float modifier)
{
	soundManager->SetMasterVolume(modifier);
	std::cout << std::to_string(modifier) + "\n";
}
