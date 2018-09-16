#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "HWindow.h"
#include "Hangman.h"
#include "GameData.h"



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//typedef Gamestate::State state;
	
	srand(time(NULL));
	Hangman* hangman = new Hangman();
	hangman->Start();
	HWindow::Get()->Clean();
	Gamestate::Clean();
	delete hangman;
	std::cin.get();
	return 0;
}