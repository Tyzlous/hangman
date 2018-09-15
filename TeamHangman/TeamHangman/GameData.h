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
	void SetWord(std::string word);
	void AddGuess(bool correctOrNot);
	void UpdateTimePlayed(sf::Time timeToAdd);
	void GameWon();
private:
	std::string username;
	std::string word;
	unsigned int totalGuesses;
	unsigned int totalCorrectGuesses;
	unsigned int gamesWon;
	sf::Time timePlayed;
	void SaveData();
	void LoadData();
	
};

