#include "Continent.h"
#include <iostream>

Continent::Continent()
{
}

Continent::Continent(std::string name, int ID, int bonus)
{
	continent_name = name;
	Continent::ID = ID;
	bonusValue = bonus;
}

Continent::~Continent()
{
}

void Continent::PrintContainedCountries()
{
	//std::vector<Country*>::iterator it;
	//for (it = containedCountries.begin(); it < containedCountries.end(); it++) {
	//	std::cout << *it.
	//}

	for (int i = 0; i < containedCountries.size(); i++)
	{
		std::cout << containedCountries[i]->get_country_name() << std::endl;
	}
}