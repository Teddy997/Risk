#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>
#include <cereal/archives/xml.hpp>
//#include "Continent.h"

class Player;
class Continent;
class Country;

class Country {
private:
	/*Member variables*/
	std::string country_name;
	Continent* containing_continent;
	Player* owner;
	bool is_owned;
	int number_of_armies;
	std::vector<Country*> connectedCountries;

public:
	Country();
	Country(std::string name, Continent& continent) : Country(name) { containing_continent = &continent; };
	Country(std::string name);
	~Country();
	std::string get_country_name();
	void setConnectedCountries(std::vector<Country*> connected) { connectedCountries = connected; }
	Continent* get_containing_continent() { return containing_continent; };
	
	void set_owned(bool value, Player& player);
	Player* get_owner();
	std::string get_owner_name();
	bool owned();
	
	void increment_armies(int amt);
	void decrement_armies(int amt);
	int get_number_of_armies();

	template<class Archive>
	void serialize(Archive & archive) {
		archive(
			CEREAL_NVP(country_name),
			CEREAL_NVP(is_owned));
	};
};

#endif