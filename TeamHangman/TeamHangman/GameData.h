#pragma once
#include <iostream>
#include <fstream>
#include <SFML/System.hpp>
class GameData
{
public:
	GameData();
	GameData(std::string username);
	~GameData();
	void SetUsername(std::string playerName);
	void AddGuess(bool correctOrNot);
	void UpdateTimePlayed(sf::Time timeToAdd);
	void GameEnded(bool winOrNot);
	std::string GetUsername();
	unsigned int GetTotalGuesses();
	unsigned int GetTotalCorrectGuesses();
	unsigned int GetGamesWon();
	sf::Time GetTimePlayed();
private:
	std::string saveFilePath = "resources/";
	std::string saveFileName = "playerdata.bin";
	std::string username;
	unsigned int totalGuesses;
	unsigned int totalCorrectGuesses;
	unsigned int gamesWon;
	sf::Time timePlayed;
	void SaveData();
	void LoadData(std::string playerName);
	bool SearchDataFor(std::string playerName);
};

