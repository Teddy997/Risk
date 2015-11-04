#pragma once
#include <string>
#include <vector>
#include "Country.h"

//class Country;

class Continent
{
public:
	Continent();
	Continent(std::string name, int ID);
	~Continent();
	std::string get_continent_name(){ return continent_name; }
	void setContainedCountries(std::vector<Country*>& contained) {containedCountries = contained;}
	void PrintContainedCountries();
	

private:
	std::string continent_name;
	int ID;
	std::vector<Country*> containedCountries;

};

