#pragma once
#include "SFML\Audio.hpp"
#include <iostream>
class HangmanSoundManager
{
public:
	HangmanSoundManager();
	~HangmanSoundManager();
	void StartMainMenuMusic();
	void StartGameMusic();
	bool isMainMenuMusicPlaying, isGameMusicPlaying;
	void PlayButtonPositive();
	void PlayButtonNegative();

private:
	sf::Music mainMenuMusic, gameMusic;
	sf::SoundBuffer buttonPositiveBuffer, buttonNegativeBuffer;
	sf::Sound buttonPositive, buttonNegative;

	const std::string AUDIO_PATH = "resources/";
};

