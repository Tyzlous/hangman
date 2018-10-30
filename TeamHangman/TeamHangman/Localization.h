#pragma once
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> dictionary;

class Localization
{
public:

	static dictionary english;
	static dictionary swedish;
};

