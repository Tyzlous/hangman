#pragma once
#include <SFML/Graphics.hpp>

class HWindow
{
public:
	~HWindow();
	static HWindow* Get();
	static sf::RenderWindow* GetWindow();
	void Clean();

private:
	HWindow();
	static HWindow* Instance;
	sf::RenderWindow* window;
};

