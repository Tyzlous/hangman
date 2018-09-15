#include "GameData.h"



GameData::GameData()
{
	username = "Name";
	word = "WORD";
	totalGuesses = 0;
	totalCorrectGuesses = 0;
	gamesWon = 0;
	timePlayed = sf::seconds(0.0f);
}

GameData::GameData(std::string username)
{
}


GameData::~GameData()
{
}

void GameData::SetUsername(std::string playerName)
{
}

void GameData::SetWord(std::string word)
{
}

void GameData::AddGuess(bool correctOrNot)
{
}

void GameData::UpdateTimePlayed(sf::Time timeToAdd)
{
}

void GameData::GameWon()
{
}

void GameData::SaveData()
{
}

void GameData::LoadData()
{
}
