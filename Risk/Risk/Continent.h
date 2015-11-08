#pragma once
#include <string>
#include <vector>
#include "Country.h"

//class Country;

class Continent
{
public:
	Continent();
	Continent(std::string name, int ID, int bonus);
	~Continent();
	std::string get_continent_name(){ return continent_name; }
	int get_bonus(){ return bonusValue; }
	void setContainedCountries(std::vector<Country*>& contained) { 
		for (int i = 0; i < contained.size(); i++) {
			contained.at(i)->set_continent_name(get_continent_name());
		}
		containedCountries = contained; 
	}
	std::vector<Country*> getContainedCountries() { return containedCountries; }
	void PrintContainedCountries();
	

private:
	int ID;
	int bonusValue;
	std::string continent_name;
	std::vector<Country*> containedCountries;

};

