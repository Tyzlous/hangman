#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "HWindow.h"
#include "CallbackButton.h"
#include "Slider.h"
#include "HangmanSoundManager.h"
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
private:
	void SetVolume(float modifier);
	void InitializeButtons();
	void InitializeSliders();
	sf::RenderWindow* window;
	Gamestate* gamestate;
	HangmanSoundManager* soundManager;
	dictionary* pickedLanguage;
	CallbackButton* menuButton;
	CallbackButton* confirmNameButton;
	CallbackButton* saveButton;
	Slider* slider;
};

