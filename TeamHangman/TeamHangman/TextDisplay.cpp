#include "TextDisplay.h"



TextDisplay::TextDisplay(sf::Vector2f position, sf::Vector2f size, std::string title)
{
	window = HWindow::GetWindow();
	InitializeDisplay(position, size, title);
}

TextDisplay::TextDisplay()
{
	window = HWindow::GetWindow();
	InitializeDisplay(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 100.0f), "DEFAULT");
}


TextDisplay::~TextDisplay()
{
	delete display;
	delete displayTexture;
	delete titleText;
	delete contentLabel;
}

void TextDisplay::Draw()
{
	window->draw(*display);
	titleText->Draw();
	contentLabel->Draw();
}

void TextDisplay::SetText(std::string newString)
{
	contentText = newString;
	ProcessTextToLines();
}

void TextDisplay::AddText(std::string stringToAdd)
{
	contentText += stringToAdd;
	ProcessTextToLines();
}

void TextDisplay::NewLineOfText(std::string text)
{
	contentText += "\n" + text;
	ProcessTextToLines();
}

void TextDisplay::InitializeDisplay(sf::Vector2f position, sf::Vector2f size, std::string title)
{
	display = new sf::RectangleShape(size);
	display->setPosition(position);
	
	displayTexture = new sf::Texture;
	displayTexture->loadFromFile(TEXTURE_DIR);

	display->setTexture(displayTexture);
	display->setFillColor(sf::Color::Blue);

	titleText = new Label(position, title, titleFontSize, sf::Color::Green);
	titleText->SetOrigin(sf::Vector2f(0.5f, 0.0f));
	titleText->SetPosition(sf::Vector2f(display->getGlobalBounds().left + display->getGlobalBounds().width * 0.5f, display->getGlobalBounds().top + 2.0f));
	
	contentLabel = new Label(sf::Vector2f(0.0f, 0.0f), "", contentFontSize, sf::Color::Green);
}

void TextDisplay::ProcessTextToLines()
{
	bool completed = false;
	std::string finalString;
	std::string tempStr;
	sf::Text tempTxt = sf::Text();
	sf::Font font;
	font.loadFromFile("arial.ttf");
	tempTxt.setFont(font);
	tempTxt.setCharacterSize(contentFontSize);
	sf::FloatRect displayRect = display->getGlobalBounds();
	sf::FloatRect lineRect;
	lineRect.left = displayRect.left + displayRect.width * 0.05f;
	lineRect.width = displayRect.width * 0.9f;
	lineRect.height = contentFontSize;
	lineRect.top = displayRect.top + titleFontSize;
	std::vector<std::string> wordVector;
	char space = ' ';

	for (int i = 0; i < contentText.size(); i++)
	{
		if (i == contentText.size() - 1)
		{
			tempStr.push_back(contentText[i]);
			wordVector.push_back(tempStr);
			tempStr.clear();
			break;
		}
		if (contentText[i] != space)
		{
			tempStr.push_back(contentText[i]);
		}
		else
		{
			tempStr.push_back(space);
			wordVector.push_back(tempStr);
			tempStr.clear();
		}
	}
	for (int i = 0; i < wordVector.size(); i++)
	{
		if (tempTxt.getLocalBounds().width <= lineRect.width)
		{
			tempStr += wordVector[i];
			tempTxt.setString(tempStr);
		}
		if (tempTxt.getLocalBounds().width > lineRect.width)
		{
			tempStr = tempStr.substr(0, tempStr.size() - wordVector[i].size()); //remove substring from tempStr
			if (tempStr.size() > 0)
			{
				tempStr += "\n"; 
				finalString += tempStr;				
			}
			tempStr = wordVector[i];
			tempTxt.setString(tempStr);
			if (tempTxt.getLocalBounds().width > lineRect.width)
			{
				std::string test = tempStr;
				while (tempTxt.getLocalBounds().width > lineRect.width)
				{
					test = tempStr;
					while (tempTxt.getLocalBounds().width > lineRect.width)
					{
						test.pop_back();
						tempTxt.setString(test);
					}
					tempStr = tempStr.substr(test.size(), tempStr.size());
					finalString += test + "\n";
					tempTxt.setString(tempStr);

				}
			}
		}
		if (i == wordVector.size() - 1)
		{
			tempTxt.setString(tempStr);
			if (tempTxt.getLocalBounds().width <= lineRect.width)
			{
				finalString += tempStr;
			}
			else
			{
				std::string test = tempStr;
				while (tempTxt.getLocalBounds().width > lineRect.width)
				{
					test = tempStr;
					while (tempTxt.getLocalBounds().width > lineRect.width)
					{
						test.pop_back();
						tempTxt.setString(test);
					}
					tempStr = tempStr.substr(test.size(), tempStr.size());
					finalString += test + "\n";
					tempTxt.setString(tempStr);
				}
			}
		}
	}
	contentLabel->SetString(finalString);
	contentLabel->SetPosition(sf::Vector2f(lineRect.left, lineRect.top));
}

void TextDisplay::SetSize(sf::Vector2f newSize)
{
	display->setSize(newSize);
	ProcessTextToLines();
}

void TextDisplay::SetTitle(std::string newString)
{
	titleText->SetString(newString);
	ProcessTextToLines();
}
