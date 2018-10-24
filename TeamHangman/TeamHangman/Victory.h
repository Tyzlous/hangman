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
};

