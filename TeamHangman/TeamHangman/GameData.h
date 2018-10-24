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
	void SaveData();
	void LoadData(std::string playerName);
	void SetUsername(std::string playerName);
	void AddGuess(bool correctOrNot);
	void UpdateTimePlayed(sf::Time timeToAdd);
	void GameEnded(bool winOrNot);
	std::string GetUsername();
	unsigned int GetTotalGuesses();
	unsigned int GetTotalCorrectGuesses();
	unsigned int GetGamesPlayed();
	unsigned int GetGamesWon();
	sf::Time GetTimePlayed();
	void printMe();
	bool SearchDataFor(std::string playerName);
	void ClearOldData();
private:
	std::string saveFilePath = "resources/";
	std::string saveFileName = "playerdata.bin";
	int toSkip = 16 + sizeof(sf::Time);
	std::string username;
	unsigned int totalGuesses;
	unsigned int totalCorrectGuesses;
	unsigned int gamesWon;
	unsigned int gamesPlayed;
	sf::Time timePlayed;
	std::string IterateFstreamAndFindUsername(std::fstream* saveFile, std::string nameToSearch);
};

