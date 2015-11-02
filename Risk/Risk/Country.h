#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>
#include <cereal/archives/xml.hpp>
#include "Player.h"

//Why is this here? I included Player.h instead
//   - Cynthia
class Player;

class Country {
private:
	/*Member variables*/
	std::string country_name;
	Player* owner;
	bool is_owned;
	int number_of_armies;

public:
	Country();
	Country(std::string name);
	~Country();
	std::string get_country_name();
	
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