#include "HangmanSoundManager.h"



HangmanSoundManager::HangmanSoundManager()
{
	if (!mainMenuMusic.openFromFile(AUDIO_PATH + "mainMenuMusic.wav"))
	{
		std::cout << "Main Menu Music failed to load brah\n";
	}
	if (!gameMusic.openFromFile(AUDIO_PATH + "gameMusic.wav"))
	{
		std::cout << "Game Music failed to load brah\n";
	}

	isMainMenuMusicPlaying = isGameMusicPlaying = false;

	if (buttonPositiveBuffer.loadFromFile(AUDIO_PATH + "buttonSoundPositive.wav"))
	{
		buttonPositive.setBuffer(buttonPositiveBuffer);
	}

	if (buttonNegativeBuffer.loadFromFile(AUDIO_PATH + "buttonSoundNegative.wav"))
	{
		buttonNegative.setBuffer(buttonNegativeBuffer);
	}

	if (victoryBuffer.loadFromFile(AUDIO_PATH + "victory.wav"))
	{
		victory.setBuffer(victoryBuffer);
	}
	masterVolume = 1.0f;
	baseVolume = 1.0f;
	SetBaseVolume(baseVolume);
}


HangmanSoundManager::~HangmanSoundManager()
{
}

void HangmanSoundManager::StartMainMenuMusic()
{
	isMainMenuMusicPlaying = true;
	isGameMusicPlaying = false;

	gameMusic.stop();
	mainMenuMusic.setLoop(true);
	mainMenuMusic.play();
}

void HangmanSoundManager::StartGameMusic()
{
	isMainMenuMusicPlaying = false;
	isGameMusicPlaying = true;

	mainMenuMusic.stop();
	gameMusic.setLoop(true);
	gameMusic.play();
}

void HangmanSoundManager::PlayButtonPositive()
{
	buttonPositive.play();
}

void HangmanSoundManager::PlayButtonNegative()
{
	buttonNegative.play();
}

void HangmanSoundManager::PlayVictory()
{
	if (isMainMenuMusicPlaying)
	{
		mainMenuMusic.stop();
		isMainMenuMusicPlaying = false;
	}
	else if (isGameMusicPlaying)
	{
		gameMusic.stop();
		isGameMusicPlaying = false;
	}
	victory.play();
}

void HangmanSoundManager::SetBaseVolume(float volume)
{
	baseVolume = volume;
	UpdateVolume();
}

void HangmanSoundManager::SetMasterVolume(float volume)
{
	masterVolume = volume;
	UpdateVolume();
}

void HangmanSoundManager::UpdateVolume()
{
	mainMenuMusic.setVolume(baseVolume * masterVolume);
	gameMusic.setVolume(baseVolume * masterVolume);
	buttonPositive.setVolume(baseVolume * masterVolume);
	buttonNegative.setVolume(baseVolume * masterVolume);
	victory.setVolume(baseVolume * masterVolume);
}
