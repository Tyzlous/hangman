#include "HWindow.h"

HWindow* HWindow::Instance = nullptr;

HWindow::HWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "HangMan", sf::Style::Titlebar | sf::Style::Close);
}


HWindow::~HWindow()
{
	if (window != nullptr)
	{
		delete window;
	}
}

HWindow * HWindow::Get()
{
	if (Instance == nullptr)
	{
		Instance = new HWindow();
	}
	return Instance;
}

sf::RenderWindow* HWindow::GetWindow()
{
	return HWindow::Get()->window;
}

void HWindow::Clean()
{
	if (Instance != nullptr)
	{
		delete Instance;
	}
}
