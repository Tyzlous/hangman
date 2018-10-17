#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "HWindow.h"
#include "CallbackButton.h"
#include "Slider.h"
#include "HangmanSoundManager.h"
#include "TextBox.h"
#include "TextDisplay.h"
class Options
{
public:
	Options();
	~Options();
	void Update();
	void Draw();
	void ButtonFunctions(std::string parameter);
	void UpdateChosenLanguage();
	void SetSoundManager(HangmanSoundManager* soundmanager);
	bool TextBoxActive();
	void TextBoxProcess(sf::Uint32 value);
	void BindCallback(std::function<void()> cbFunction);
	void UpdateStatDisplay();
private:
	void SetVolume(float modifier);
	void InitializeButtons();
	void InitializeLanguagebuttons();
	void InitializeSliders();
	void InitializeTextBoxes();
	void UpdateLanguageButtons();
	sf::RenderWindow* window;
	Gamestate* gamestate;
	HangmanSoundManager* soundManager;
	dictionary* pickedLanguage;
	std::vector<CallbackButton*> callbackButtonAddresses;
	CallbackButton* menuButton;
	CallbackButton* confirmNameButton;
	CallbackButton* saveButton;
	CallbackButton* loadButton;
	CallbackButton* createButton;
	CallbackButton* revertButton;
	Slider* slider;
	TextBox* textBox;
	TextDisplay* statDisplay;
	std::function<void()> callback;
	LocalizedLabel* languageLabel;
	sf::RectangleShape* flagRect1;
	sf::RectangleShape* flagRect2;
	sf::Texture* sweFlagTexture;
	sf::Texture* engFlagTexture;
	bool isDefaultProfile = true;
};

