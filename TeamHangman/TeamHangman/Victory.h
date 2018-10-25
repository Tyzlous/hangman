#pragma once
#include <vector>
#include "Gamestate.h"
#include "CallbackButton.h"
#include "HangmanSoundManager.h"
class Victory
{
public:
	Victory();
	~Victory();
	void Update();
	void Draw();
	void SetSoundManager(HangmanSoundManager* soundManager);
	void UpdateLanguage();
	void UpdateText(bool GameWasWon);
private:
	void InitializeText();
	void InitializeButtons();
	void ChangeGamestate(std::string parameter);
	HangmanSoundManager* soundManager;
	sf::RenderWindow* window;
	Gamestate* gamestate;
	std::vector<CallbackButton*> buttons;
	LocalizedLabel* EndText;
	bool playMusic;
	void InitializeBackground();
	sf::Texture* backgroundTexture;
	sf::RectangleShape* backgroundImage;
	sf::Texture* titleTexture;
	sf::RectangleShape* titleImage;
	const std::string BACKGROUND_IMAGE_PATH = "resources/mainMenuBackground.png";
	const std::string TITLE_IMAGE_PATH = "resources/title.png";
};

