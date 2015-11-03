#pragma once
#include <string>
#include <vector>
#include "Country.h"

class Continent
{
public:
	Continent();
	Continent(std::string name, int ID);
	~Continent();

private:
	std::string continent_name;
	int ID;
	std::vector<Country*> countriesContained;

};

