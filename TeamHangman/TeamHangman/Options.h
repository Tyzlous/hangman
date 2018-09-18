#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "HWindow.h"
#include "CallbackButton.h"
class Options
{
public:
	Options();
	~Options();
	void Update();
	void Draw();
	void InitializeButtons();
	void ButtonFunctions(std::string parameter);
	void UpdateChosenLanguage();
private:
	sf::RenderWindow* window;
	Gamestate* gamestate;
	dictionary* pickedLanguage;
	CallbackButton* menuButton;
	CallbackButton* confirmNameButton;
	CallbackButton* saveButton;
};

