#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "HWindow.h"
#include "CallbackButton.h"
class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void update();
	void draw();
	void fuckOff(std::string parameter);
	void InitializeButtons();
private:
	sf::RenderWindow* window;
	Gamestate* gamestate;
	
	CallbackButton* topButton;
	CallbackButton* middleButton;
	CallbackButton* bottomButton;

};

