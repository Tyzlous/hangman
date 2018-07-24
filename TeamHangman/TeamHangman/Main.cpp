#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamestate.h"


int main()
{
	typedef Gamestate::State state;
	Gamestate* gameState = Gamestate::Get();
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}