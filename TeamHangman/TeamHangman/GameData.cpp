#include "GameData.h"



GameData::GameData()
{
	username = "Name";
	totalGuesses = 0;
	totalCorrectGuesses = 0;
	gamesWon = 0;
	timePlayed = sf::seconds(0.0f);
}

GameData::GameData(std::string playerName)
{
	username = playerName;
	totalGuesses = 0;
	totalCorrectGuesses = 0;
	gamesWon = 0;
	timePlayed = sf::seconds(0.0f);
	if (SearchDataFor(playerName))
	{
		LoadData(playerName);
	}
}


GameData::~GameData()
{
}

void GameData::SetUsername(std::string playerName)
{
	for (int i = 0; i < username.size(); i++)
	{
		username.pop_back();
	}
	username.clear();
	if (username.empty())
	{
		username = playerName;
	}
}

void GameData::AddGuess(bool correctOrNot)
{
	totalGuesses++;
	if (correctOrNot)
	{
		totalCorrectGuesses++;
	}
}

void GameData::UpdateTimePlayed(sf::Time timeToAdd)
{
	timePlayed += timeToAdd;
}

void GameData::GameEnded(bool winOrNot)
{
	gamesWon++;
}

std::string GameData::GetUsername()
{
	return std::string();
}

unsigned int GameData::GetTotalGuesses()
{
	return totalGuesses;
}

unsigned int GameData::GetTotalCorrectGuesses()
{
	return totalCorrectGuesses;
}

unsigned int GameData::GetGamesWon()
{
	return gamesWon;
}

sf::Time GameData::GetTimePlayed()
{
	return timePlayed;
}

void GameData::SaveData()
{
	using namespace std;
	std::string file = saveFilePath + saveFileName;
	int size;
	if (SearchDataFor(username))
	{
		fstream saveFile(file, ios::out | ios::in| ios::binary);
		if (!saveFile.is_open())
		{
			cout << "Error opening SaveFile " + file << endl;
		}
		else
		{
			std::string nameFetched;
			int toSkip = 12 + sizeof(sf::Time);

			while (username.compare(nameFetched) != 0 && !saveFile.eof())
			{
				saveFile.read((char*)&size, sizeof(int));
				nameFetched.reserve(size);
				saveFile.read((char*)&nameFetched, size);
				if (username.compare(nameFetched) != 0)
				{
					saveFile.seekg(toSkip, ios_base::cur);
					for (int i = 0; i < nameFetched.size(); i++)
					{
						nameFetched.pop_back();
					}
					nameFetched.clear();
				}
			}
			if (username.compare(nameFetched) == 0)
			{
				saveFile.seekp(saveFile.tellg);
				saveFile.write((char*)&totalGuesses, sizeof(int));
				saveFile.write((char*)&totalCorrectGuesses, sizeof(int));
				saveFile.write((char*)&gamesWon, sizeof(int));
				saveFile.write((char*)&timePlayed, sizeof(sf::Time));
			}
			saveFile.close();
		}
		
	}
	else
	{
		fstream saveFile(file, ios::out | ios::app | ios::binary);
		if (!saveFile.is_open())
		{
			cout << "Error opening SaveFile " + file << endl;
		}
		else 
		{
			size = username.size();
			saveFile.write((char *)&size, sizeof(int));
			saveFile.write((char*)&username, size);
			saveFile.write((char*)&totalGuesses, sizeof(int));
			saveFile.write((char*)&totalCorrectGuesses, sizeof(int));
			saveFile.write((char*)&gamesWon, sizeof(int));
			saveFile.write((char*)&timePlayed, sizeof(sf::Time));
			saveFile.close();
		}

	}

}

void GameData::LoadData(std::string playerName)
{
	using namespace std;
	std::string file = saveFilePath + saveFileName;
	int size;
	fstream saveFile(file, ios::in | ios::binary);
	if (!saveFile.is_open())
	{
		cout << "Error opening SaveFile " + file << endl;
	}
	else
	{
		std::string nameFetched;
		int toSkip = 12 + sizeof(sf::Time);

		while (playerName.compare(nameFetched) != 0 && !saveFile.eof())
		{
			saveFile.read((char*)&size, sizeof(int));
			nameFetched.reserve(size);
			saveFile.read((char*)&nameFetched, size);
			if (playerName.compare(nameFetched) != 0)
			{
				saveFile.seekg(toSkip, ios_base::cur);
				for (int i = 0; i < nameFetched.size(); i++)
				{
					nameFetched.pop_back();
				}
				nameFetched.clear();
			}
		}
		if (playerName.compare(nameFetched) == 0)
		{
			username = nameFetched;
			saveFile.read((char*)&totalGuesses, sizeof(int));
			saveFile.read((char*)&totalCorrectGuesses, sizeof(int));
			saveFile.read((char*)&gamesWon, sizeof(int));
			saveFile.read((char*)&timePlayed, sizeof(sf::Time));
		}

		saveFile.close();
	}
}

bool GameData::SearchDataFor(std::string playerName)
{
	bool usernameIsFound = false;
	using namespace std;
	std::string file = saveFilePath + saveFileName;
	std::string nameFetched;
	int size;
	int toSkip = 12 + sizeof(sf::Time);
	fstream saveFile(file, ios::in | ios::binary);
	if (!saveFile.is_open())
	{
		cout << "Error opening SaveFile " + file << endl;
	}
	else
	{
		while (playerName.compare(nameFetched) !=0 && !saveFile.eof())
		{
			saveFile.read((char*)&size, sizeof(int));
			nameFetched.reserve(size);
			saveFile.read((char*)&nameFetched, size);
			if (username.compare(nameFetched) != 0)
			{
				saveFile.seekg(toSkip, ios_base::cur);
				for (int i = 0; i < nameFetched.size(); i++)
				{
					nameFetched.pop_back();
				}
				nameFetched.clear();
			}
		}
		saveFile.close();
	}
	return usernameIsFound;
}
