#pragma once
#include <string>
#include <vector>

class Country;

class Continent
{
public:
	Continent();
	Continent(std::string name, int ID);
	~Continent();
	void setContainedCountries(std::vector<Country*> contained);

private:
	std::string continent_name;
	int ID;
	std::vector<Country*> containedCountries;

};

