#include "TextDisplay.h"



TextDisplay::TextDisplay(sf::Vector2f position, sf::Vector2f size, std::string title)
{
	window = HWindow::GetWindow();
	InitializeDisplay(position, size, title);
}

TextDisplay::TextDisplay()
{
	window = HWindow::GetWindow();
	InitializeDisplay(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 100.0f), "TEST");
}


TextDisplay::~TextDisplay()
{
	delete display;
	delete displayBackground;
	delete titleText;
	for (int i = 0; i < textLines.size(); i++)
	{
		delete textLines[i];
	}
}

void TextDisplay::Draw()
{
	window->draw(*display);
	titleText->Draw();
}

void TextDisplay::NewLineOfText(std::string text)
{
}

void TextDisplay::InitializeDisplay(sf::Vector2f position, sf::Vector2f size, std::string title)
{
	display = new sf::RectangleShape(size);
	display->setPosition(position);
	
	displayBackground = new sf::Texture;
	displayBackground->loadFromFile(TEXTURE_DIR);

	display->setTexture(displayBackground);
	display->setFillColor(sf::Color::Blue);

	titleText = new Label(position, title, 30, sf::Color::Green);

	/*display->setSize(sf::Vector2f(titleText->GetGlobalBounds().width * 1.2f, titleText->GetGlobalBounds().height * 1.2f));*/
	titleText->SetOrigin(sf::Vector2f(0.5f, 0.0f));
	titleText->SetPosition(sf::Vector2f(display->getGlobalBounds().left + display->getGlobalBounds().width * 0.5f, display->getGlobalBounds().top + display->getGlobalBounds().height * 0.05f));

}

void TextDisplay::UpdateRect()
{
}
