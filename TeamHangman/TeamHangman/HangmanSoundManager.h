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
	void PlayVictory();
	void SetVolume(float volume);

private:
	sf::Music mainMenuMusic, gameMusic;
	sf::SoundBuffer buttonPositiveBuffer, buttonNegativeBuffer, victoryBuffer;
	sf::Sound buttonPositive, buttonNegative, victory;

	const std::string AUDIO_PATH = "resources/";
};

