#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "HWindow.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	typedef Gamestate::State state;
	Gamestate* gameState = Gamestate::Get();
	
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::RenderWindow* window = HWindow::GetWindow();
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		window->draw(shape);
		window->display();
	}

	HWindow::Get()->Clean();
	Gamestate::Clean();


	return 0;
}