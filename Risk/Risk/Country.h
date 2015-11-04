#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>
#include <cereal/archives/xml.hpp>

class Player;
class Country;

class Country {
private:
	/*Member variables*/
	std::string country_name;
	Player* owner;
	bool is_owned;
	int number_of_armies;
	std::vector<Country*> connectedCountries;

public:
	Country();
	Country(std::string name);
	~Country();
	std::string get_country_name();
	void setConnectedCountries(std::vector<Country*> connected) { connectedCountries = connected; }
	
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