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
private:
	void InitializeState();
	void InitializeButtons();
	void ChangeGamestate(std::string parameter);
	HangmanSoundManager* soundManager;
	sf::RenderWindow* window;
	Gamestate* gamestate;
	std::vector<CallbackButton*> buttons;
	LocalizedLabel* winText;
	bool playMusic;
};

