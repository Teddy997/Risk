#include "Continent.h"


Continent::Continent()
{
}

Continent::Continent(std::string name, int ID)
{
	continent_name = name;
	Continent::ID = ID;
}

Continent::~Continent()
{
}

void Continent::setContainedCountries(std::vector<Country*> contained) {
	containedCountries = contained;
}
