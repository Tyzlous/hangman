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
	void ChangeGamestate(std::string parameter);
private:
	sf::RenderWindow* window;
	Gamestate* gamestate;
	
	CallbackButton* topButton;
	CallbackButton* middleButton;
	CallbackButton* bottomButton;

	sf::Texture* texture = nullptr;
	sf::RectangleShape* backgroundImage = nullptr;

	const std::string BACKGROUND_IMAGE_PATH = "resources/mainMenuBackground.png";

};

